/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libcorewar_get_asm_file.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 11:47:27 by afeuerst          #+#    #+#             */
/*   Updated: 2019/11/23 13:15:52 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcorewar_get_asm_file.h"

static const struct s_libcorewar_ref_opcode_get		g_opcodes_get[256] =
{
	[0x01] = {"live",  1, 10,   0, 0, 0x01, 0, {T_DIR}},
	[0x02] = {"ld",    2, 5,    1, 0, 0x02, 0, {T_DIR | T_IND, T_REG}},
	[0x03] = {"st",    2, 5,    1, 0, 0x03, 0, {T_REG, T_IND | T_REG}},
	[0x04] = {"add",   3, 10,   1, 0, 0x04, 0, {T_REG, T_REG, T_REG}},
	[0x05] = {"sub",   3, 10,   1, 0, 0x05, 0, {T_REG, T_REG, T_REG}},
	[0x06] = {"and",   3, 6,    1, 0, 0x06, 0, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}},
	[0x07] = {"or",    3, 6,    1, 0, 0x07, 0, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}},
	[0x08] = {"xor",   3, 6,    1, 0, 0x08, 0, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}},
	[0x09] = {"zjmp",  1, 20,   0, 1, 0x09, 0, {T_DIR}},
	[0x0a] = {"ldi",   3, 25,   1, 1, 0x0a, 0, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}},
	[0x0b] = {"sti",   3, 25,   1, 1, 0x0b, 0, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}},
	[0x0c] = {"fork",  1, 800,  0, 1, 0x0c, 0, {T_DIR}},
	[0x0d] = {"lld",   2, 10,   1, 0, 0x0d, 0, {T_DIR | T_IND, T_REG}},
	[0x0e] = {"lldi",  3, 50,   1, 1, 0x0e, 0, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}},
	[0x0f] = {"lfork", 1, 1000, 0, 1, 0x0f, 0, {T_DIR}},
	[0x10] = {"aff",   1, 2,    1, 0, 0x10, 0, {T_REG}}
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
							ft_asprintf(&target->label, "%s%d", file->labels_prefix, file->labels_count++);
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
		opcode->parameters[index] = (int)__builtin_bswap16(*(short*)content) & 0xFFFF;
		addr = opcode->start + opcode->parameters[index];
		content -= 2;
	}
	else
	{
		opcode->parameters[index] = __builtin_bswap32(*(int*)content);
		addr = opcode->start + opcode->parameters[index];
	}
	if (opcode->parameters[index] &&
			addr >= (file->content + sizeof(struct s_asm_header)) && addr < file->content_end &&
			g_opcodes_get[(int)*addr & 0xFF].name)
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
	return (file);
}

struct s_libcorewar_asm_file						*libcorewar_get_asm_file(const char *const named, char **const error, const char *const prefix)
{
	const int										fd = open(named, O_RDONLY);
	struct s_libcorewar_asm_file					*file;
   
	if (!(file = malloc(sizeof(struct s_libcorewar_asm_file))))
		return (libcorewar_error("cannot allocate", error, NULL));
	if (fd < 0)
		return (libcorewar_error("cannot open", error, file, NULL));
	if (fstat(fd, &file->content_stat) < 0)
		return (libcorewar_error("cannot fstat", error, file, NULL));
	if ((file->content = mmap(NULL, file->content_stat.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (libcorewar_error("cannot mmap", error, file, NULL));
	file->content_end = file->content + file->content_stat.st_size;
	if (file->content_stat.st_size < sizeof(int))
		return (libcorewar_error("file to small for checking magic number", error, file, NULL));
	file->header = (void*)file->content;
	//f->header->magic = __builtin_bswap32(f->header->magic);
	if (__builtin_bswap32(file->header->magic) != COREWAR_EXEC_MAGIC)
		return (libcorewar_error("bad magic number", error, file, NULL));
	//if ((off_t)f->header->prog_size != f->content_stat.st_size)
	//	return (libcorewar_error("bad file size", error, f, NULL));
	file->opcodes = NULL;
	if (!(file->labels_prefix = prefix))
		file->labels_prefix = "label_";
	file->labels_count = 0;
	return (get_asm_file_opcodes(file, error));
}
