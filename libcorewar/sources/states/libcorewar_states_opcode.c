/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libcorewar_states_opcode.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:24:08 by afeuerst          #+#    #+#             */
/*   Updated: 2019/11/18 15:59:38 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcorewar_get_src_file.h"

static const int								g_opcodes_chars[256] =
{
	['a' ... 'z'] = 1,
	['0' ... '9'] = 1,
	['_'] = 1
};

static const struct s_libcorewar_ref_opcode_get	g_opcodes_get[256] =
{
	[0x6d] = {"live",  1, 10,   0, 0, 0x01, 0, {T_DIR}},
	[0xb4] = {"ld",    2, 5,    1, 0, 0x02, 0, {T_DIR | T_IND, T_REG}},
	[0x9a] = {"st",    2, 5,    1, 0, 0x03, 0, {T_REG, T_IND | T_REG}},
	[0x38] = {"add",   3, 10,   1, 0, 0x04, 0, {T_REG, T_REG, T_REG}},
	[0x54] = {"sub",   3, 10,   1, 0, 0x05, 0, {T_REG, T_REG, T_REG}},
	[0x2c] = {"and",   3, 6,    1, 0, 0x06, 0, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}},
	[0xa4] = {"or",    3, 6,    1, 0, 0x07, 0, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}},
	[0x5c] = {"xor",   3, 6,    1, 0, 0x08, 0, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}},
	[0xf2] = {"zjmp",  1, 20,   0, 1, 0x09, 0, {T_DIR}},
	[0x01] = {"ldi",   3, 25,   1, 1, 0x0a, 0, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}},
	[0x5d] = {"sti",   3, 25,   1, 1, 0x0b, 0, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}},
	[0x23] = {"fork",  1, 800,  0, 1, 0x0c, 0, {T_DIR}},
	[0x1c] = {"lld",   2, 10,   1, 0, 0x0d, 0, {T_DIR | T_IND, T_REG}},
	[0x51] = {"lldi",  3, 50,   1, 1, 0x0e, 0, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}},
	[0x83] = {"lfork", 1, 1000, 0, 1, 0x0f, 0, {T_DIR}},
	[0x3e] = {"aff",   1, 2,    1, 0, 0x10, 0, {T_REG}}
};

static char										*state_opcode_parameter(
		struct s_libcorewar_src_file *const file,
		const struct s_libcorewar_ref_opcode_get *const ref,
		char *content, char **const error)
{
	ft_printf("%s\n", ref->name);
	while (content < file->content_end && *content != '\n')
		++content;
	if (*content == '\n')
		++content;
	return (content);
}

char											*libcorewar_state_opcode(
		struct s_libcorewar_src_file *const file,
		char *content, int *const state, char **const error)
{
	int											length;
	char										*world;
	struct s_libcorewar_opcode_src				*op;
	unsigned char								hash;
	const t_libcorewar_ref_opcode_get			*ref;

	world = ft_static_world(content, file->content_end, g_opcodes_chars, &length);
	if (!(op = ft_memalloc(sizeof(struct s_libcorewar_opcode_src))))
		return (libcorewar_error("cannot allocate", error, NULL));
	if (*(content + length) == ':')
	{
		op->label = ft_memcopy(content, length + 1);
		content = libcorewar_state_whitespace(file, content += length + 1, state, error);
		world = ft_static_world(content, file->content_end, g_opcodes_chars, &length);
	}
	hash = ft_hash_src(world, (size_t)length);
	if (!(ref = g_opcodes_get + hash)->name || ft_strcmp(ref->name, world))
		return (libcorewar_error("unknow opcode", error, NULL));
	content += length;
	return (state_opcode_parameter(file, ref, content, error));
}













