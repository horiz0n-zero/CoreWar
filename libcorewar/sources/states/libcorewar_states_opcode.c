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

static const int								g_opcodes_labels[256] =
{
	['a' ... 'z'] = 1,
	['0' ... '9'] = 1,
	['_'] = 1,
	[':'] = 1
};

static const struct s_libcorewar_ref_opcode_get	g_opcodes_get[256] =
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

char											*libcorewar_state_opcode(
		struct s_libcorewar_src_file *const file,
		char *content, int *const state, char **const error)
{
	int								index;
	int								length;
	char							*world;
	struct s_libcorewar_opcode_src	*op;

	world = ft_static_world(content, file->content_end, g_opcodes_chars, &length);
	if (!(op = ft_memalloc(sizeof(struct s_libcorewar_opcode_src))))
		return (libcorewar_error("cannot allocate", error, NULL));
	if (*(content + length) == ':')
	{
		op->label = ft_memcopy(content, length + 1);
		content = libcorewar_state_whitespace(file, content += length + 1, state, error);
		world = ft_static_world(content, file->content_end, g_opcodes_chars, &length);
	}
	content = libcorewar_state_whitespace(file, content, state, error);
	return (content);
}













