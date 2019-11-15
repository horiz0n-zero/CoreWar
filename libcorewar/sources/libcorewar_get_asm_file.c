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

static const struct s_libcorewar_ref_opcode_get		g_opcodes_get[256] =
{
	[0x01] = {"live", 1, 10, {T_DIR}},
	[0x02] = {"ld", 2, 5, {T_DIR | T_IND, T_REG}},
	[0x03] = {"st", 2, 5, {T_REG, T_IND | T_REG}},
	[0x04] = {"add", 3, 10, {T_REG, T_REG, T_REG}},
	[0x05] = {"sub", 3, 10, {T_REG, T_REG, T_REG}},
	[0x06] = {"and", 3, 6, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}},
	[0x07] = {"or", 3, 6, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}},
	[0x08] = {"xor", 3, 6, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}},
	[0x09] = {"zjmp", 1, 20, {T_DIR}},
	[0x0a] = {"ldi", 3, 25, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}},
	[0x0b] = {"sti", 3, 25, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}},
	[0x0c] = {"fork", 1, 800, {T_DIR}},
	[0x0d] = {"lld", 2, 10, {T_DIR | T_IND, T_REG}},
	[0x0e] = {"lldi", 3, 50, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}},
	[0x0f] = {"lfork", 1, 1000, {T_DIR}},
	[0x10] = {"aff", 1, 2, {T_REG}}
};
#include <stdio.h>
static char											*get_asm_file_opcodes_content(struct s_libcorewar_opcode_get *const opcode, char *content, char **const error)
{
	int												index;

	index = 0;
	while (index < opcode->ref->parameters)
	{
		opcode->parameters[index] = __builtin_bswap32(*(int*)content);
		content += sizeof(int);
		printf("%u ", opcode->parameters[index]);
		++index;
	}
	return (content);
}

static struct s_libcorewar_asm_file					*get_asm_file_opcodes(struct s_libcorewar_asm_file *const file, char **const error)
{
	char *const										end = file->content + file->content_stat.st_size;
	char											*content;
	const struct s_libcorewar_ref_opcode_get		*ref;
	struct s_libcorewar_opcode_get					**nopcodes;

	nopcodes = &file->opcodes;
	content = file->content + sizeof(struct s_asm_header);
	while (content < end)
	{
		ref = g_opcodes_get + *content++;
		if (ref->name)
		{
			printf("%s:", ref->name);
			if (!(*nopcodes = malloc(sizeof(struct s_libcorewar_opcode_get))))
				return (libcorewar_error("cannot allocate", error, file->content, NULL));
			(*nopcodes)->ref = ref;
			if (!(content = get_asm_file_opcodes_content(*nopcodes, content, error)))
				return (NULL);
			nopcodes = &(*nopcodes)->next;
			printf("\n");
		}
		else
			printf("bad opcode : %hhx\n", *(content - 1));
	}
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
