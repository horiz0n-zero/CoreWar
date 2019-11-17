/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libcorewar_get_asm_file.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 11:47:27 by afeuerst          #+#    #+#             */
/*   Updated: 2019/11/15 16:00:22 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcorewar_get_asm_file.h"
#include <stdio.h>

void												print_opcode(struct s_libcorewar_opcode_get *const op)
{
	int												index;

	index = 0;
	if (op->label)
		printf("%s: %s ", op->label, op->ref->name);
	else
		printf("%s ", op->ref->name);
	while (index < op->ref->parameters)
	{
		if (op->parameters_type[index] == REG_CODE)
			printf("r%hhu", (unsigned char)op->parameters[index]);
		else if (op->parameters_type[index] == IND_CODE)
			printf("%hu", (unsigned short)op->parameters[index]);
		else
		{
			if (op->label)
			{
				if (op->parameters[index] < 0)
					printf("%%:%s", op->parameters_labels[index]);
				else	
					printf("%%:%s", op->parameters_labels[index]);
			}
			else
				printf("%%%u", op->parameters[index]);
		}
		if (++index < op->ref->parameters)
			printf(", ");
	}
	printf("\n");
	fflush(stdout);
}

void												print_opcodes(struct s_libcorewar_asm_file *const file)
{
	struct s_libcorewar_opcode_get					*op;

	op = file->opcodes;
	while (op)
	{
		print_opcode(op);
		op = op->next;
	}
}

static const struct s_libcorewar_ref_opcode_get		g_opcodes_get[256] =
{
	[0x01] = {"live",  1, 10,   0, 0, {T_DIR}},
	[0x02] = {"ld",    2, 5,    1, 0, {T_DIR | T_IND, T_REG}},
	[0x03] = {"st",    2, 5,    1, 0, {T_REG, T_IND | T_REG}},
	[0x04] = {"add",   3, 10,   1, 0, {T_REG, T_REG, T_REG}},
	[0x05] = {"sub",   3, 10,   1, 0, {T_REG, T_REG, T_REG}},
	[0x06] = {"and",   3, 6,    1, 0, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}},
	[0x07] = {"or",    3, 6,    1, 0, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}},
	[0x08] = {"xor",   3, 6,    1, 0, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}},
	[0x09] = {"zjmp",  1, 20,   0, 1, {T_DIR}},
	[0x0a] = {"ldi",   3, 25,   1, 1, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}},
	[0x0b] = {"sti",   3, 25,   1, 1, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}},
	[0x0c] = {"fork",  1, 800,  0, 1, {T_DIR}},
	[0x0d] = {"lld",   2, 10,   1, 0, {T_DIR | T_IND, T_REG}},
	[0x0e] = {"lldi",  3, 50,   1, 1, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}},
	[0x0f] = {"lfork", 1, 1000, 0, 1, {T_DIR}},
	[0x10] = {"aff",   1, 2,    1, 0, {T_REG}}
};

static const int									g_parameters_size[] =
{
	[REG_CODE] = REG_SIZE,
	[IND_CODE] = IND_SIZE,
	[DIR_CODE] = DIR_SIZE
};

static void											get_asm_file_resolve_labels(
	struct s_libcorewar_asm_file *const file, char **const error)
{
	struct s_libcorewar_opcode_get					*op;
	struct s_libcorewar_opcode_get					*target;
	int												index;

	op = file->opcodes;
	while (op)
	{
		index = 0;
		while (index < op->ref->parameters)
		{
			if (op->parameters_type[index] == DIR_CODE && op->parameters_labels[index])
			{
				target = file->opcodes;
				while (target)
				{
					if (target->start == (const char*)op->parameters_labels[index])
					{
						if (!target->label)
							target->label = "label";
						op->parameters_labels[index] = target->label;
						break;
					}
					target = target->next;
				}
			}
			++index;
		}
		op = op->next;
	}
}

static char											*get_asm_file_opcodes_direct(
	struct s_libcorewar_asm_file *const file,
	struct s_libcorewar_opcode_get *const opcode,
	char *content, const int index)
{
	char											*addr;

	if (opcode->ref->parameters_direct_small)
	{
		opcode->parameters[index] = (int)__builtin_bswap16(*(short*)content);
		return (content - 2);
	}
	opcode->parameters[index] = __builtin_bswap32(*(int*)content);
	addr = opcode->start + opcode->parameters[index];
	if (addr >= (file->content + sizeof(struct s_asm_header)) && addr < file->content_end && g_opcodes_get[*addr].name)
		opcode->parameters_labels[index] = addr;
	else
		opcode->parameters_labels[index] = NULL;
	return (content);
}

static char											*get_asm_file_opcodes_content(
	struct s_libcorewar_asm_file *const file,
	struct s_libcorewar_opcode_get *const opcode,
	char *content, char **const error)
{
	int												index;
	int												r;
	char											encode;// 10(DIR,4) 11(IND,2) 01(REG,1)

	index = 0;
	if (opcode->ref->parameters_encoding)
		encode = *content++;
	else
		encode = 0b10000000;
	while (index < opcode->ref->parameters)
	{
		r = (((int)encode << (index << 1)) >> 6) & 0b00000011;
		if (r == REG_CODE)
			opcode->parameters[index] = (int)*content;
		else if (r == IND_CODE)
			opcode->parameters[index] = (int)*(short*)content;
		else if (r == DIR_CODE)
			content = get_asm_file_opcodes_direct(file, opcode, content, index);
		else
			return (libcorewar_error("bad parameter encoding", error, opcode, NULL));
		opcode->parameters_type[index++] = r;
		content += g_parameters_size[r];
	}
	return (content);
}

static struct s_libcorewar_asm_file					*get_asm_file_opcodes(struct s_libcorewar_asm_file *const file, char **const error)
{
	char											*content;
	const struct s_libcorewar_ref_opcode_get		*ref;
	struct s_libcorewar_opcode_get					**nopcodes;

	nopcodes = &file->opcodes;
	content = file->content + sizeof(struct s_asm_header);
	while (content < file->content_end)
	{
		ref = g_opcodes_get + *content;
		if (ref->name)
		{
			if (!(*nopcodes = malloc(sizeof(struct s_libcorewar_opcode_get))))
				return (libcorewar_error("cannot allocate", error, file->content, NULL));
			(*nopcodes)->ref = ref;
			(*nopcodes)->start = content++;
			(*nopcodes)->label = NULL;
			if (!(content = get_asm_file_opcodes_content(file, *nopcodes, content, error)))
				return (NULL);
			nopcodes = &(*nopcodes)->next;
		}
		else
			return (libcorewar_error("bad opcode", error, file, NULL));
	}
	get_asm_file_resolve_labels(file, error);
	print_opcodes(file);
	return (file);
}

struct s_libcorewar_asm_file						*libcorewar_get_asm_file(const char *const file, char **const error)
{
	const int										fd = open(file, O_RDONLY);
	struct s_libcorewar_asm_file					*f;
   
	if (!(f = malloc(sizeof(struct s_libcorewar_asm_file))))
		return (libcorewar_error("cannot allocate", error, NULL));
	if (fd < 0)
		return (libcorewar_error("cannot open", error, f, NULL));
	if (fstat(fd, &f->content_stat) < 0)
		return (libcorewar_error("cannot fstat", error, f, NULL));
	if ((f->content = mmap(NULL, f->content_stat.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (libcorewar_error("cannot mmap", error, f, NULL));
	f->content_end = f->content + f->content_stat.st_size;
	if (f->content_stat.st_size < sizeof(int))
		return (libcorewar_error("file to small for checking magic number", error, f, NULL));
	f->header = (void*)f->content;
	//f->header->magic = __builtin_bswap32(f->header->magic);
	if (__builtin_bswap32(f->header->magic) != COREWAR_EXEC_MAGIC)
		return (libcorewar_error("bad magic number", error, f, NULL));
	//if ((off_t)f->header->prog_size != f->content_stat.st_size)
	//	return (libcorewar_error("bad file size", error, f, NULL));
	f->opcodes = NULL;
	return (get_asm_file_opcodes(f, error));
}
