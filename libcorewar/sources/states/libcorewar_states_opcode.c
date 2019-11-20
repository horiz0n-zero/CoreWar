/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libcorewar_states_opcode.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:24:08 by afeuerst          #+#    #+#             */
/*   Updated: 2019/11/19 16:43:21 by afeuerst         ###   ########.fr       */
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

static const struct s_libcorewar_ref_opcode_get	*g_ref = NULL;
static struct s_libcorewar_src_file				*g_file = NULL;

static void										state_add_opcode(
		struct s_libcorewar_src_file *const file,
		struct s_libcorewar_opcode_src *const op)
{
	static struct s_libcorewar_opcode_src		*last = NULL;

	if (!file->opcodes)
	{
		last = NULL;
		file->opcodes = op;
		last = op;
	}
	else
	{
		last->next = op;
		last = op;
	}
}

static char										*state_opcode_indirect(
		struct s_libcorewar_opcode_src *const op,
		char *content, char **const error, const int index)
{
	static const int							dirs_minmax[2] = {SHRT_MIN, SHRT_MAX};
	t_src_number								func;

	op->parameters_type[index] = T_IND;
	if (!(op->ref->parameters_type[index] & T_IND))
	{
		*error = "cannot be a ind";
		return (content);
	}
	if (*content == '-' && ++content)
		func = ft_src_number;
	else
		func = ft_src_unumber;
	if (*content >= '0' && *content <= '9')
	{
		op->parameters[index] = func(content, dirs_minmax, error);
		content = libcorewar_state_numbers(NULL, content, NULL, error);
	}
	else
		*error = "illegal char in parameter";
	return (content);
}

static char										*state_opcode_reg(
		struct s_libcorewar_opcode_src *const op,
		char *content, char **const error, const int index)
{
	static const int							reg_minmax[2] = {1, REG_NUMBER};

	op->parameters_type[index] = T_REG;
	if (!(op->ref->parameters_type[index] & T_REG))
		*error = "waiting for a reg";
	else if (*content == '-')
		*error = "non negative register allowed";
	else
	{
		if (*content >= '0' && *content <= '9')
		{
			op->parameters[index] = ft_src_unumber(content, reg_minmax, error);
			content = libcorewar_state_numbers(NULL, content, NULL, error);
		}
		else
			*error = "register must be a number";
	}
	return (content);
}

static char										*state_opcode_direct(
		struct s_libcorewar_opcode_src *const op,
		char *content, char **const error, const int index)
{
	static const int							dir_minmax[2] = {INT_MIN, INT_MAX};
	static const int							dirs_minmax[2] = {SHRT_MIN, SHRT_MAX};
	t_src_number								func;
	int											length;

	op->parameters_type[index] = T_DIR;
	if (!(op->ref->parameters_type[index] & T_DIR))
		*error = "waiting for a dir";
	else if (*content == ':')
	{
		if (!g_opcodes_chars[*++content])
			*error = "bad formatted label";
		else
		{
			op->parameters_labels[index] = ft_memcopy(ft_static_world(content, g_file->content_end, g_opcodes_chars, &length), length);
			content += length;
		}
	}
	else
	{
		if (*content == '-' && ++content)
			func = ft_src_number;
		else
			func = ft_src_unumber;
		if (*content >= '0' && *content <= '9')
		{
			if (op->ref->parameters_direct_small)
				op->parameters[index] = func(content, dirs_minmax, error);
			else
				op->parameters[index] = func(content, dir_minmax, error);
			content = libcorewar_state_numbers(NULL, content, NULL, error);
		}
		else
			*error = "dir not a ";
	}
	return (content);
}

static char										*state_opcode_parameter(
		struct s_libcorewar_src_file *const file,
		struct s_libcorewar_opcode_src *const op,
		char *content, char **const error)
{
	int											index;

	index = 0;
	op->ref = g_ref;
	while (!*error && index < g_ref->parameters)
	{
		if (!index)
			content = libcorewar_state_whitespace(file, content, NULL, error);
		else
			content = libcorewar_state_virguspace(file, content, NULL, error);
		if (*content == DIRECT_CHAR)
			content = state_opcode_direct(op, ++content, error, index);
		else if (*content >= '0' && *content <= '9')
			content = state_opcode_indirect(op, content, error, index);
		else if (*content == REG_CHAR)
			content = state_opcode_reg(op, ++content, error, index);
		else
			ft_asprintf(error, "bad parameters for %s", op->ref->name);
		++index;
	}
	if (!*error)
		state_add_opcode(file, op);
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

	g_file = file;
	world = ft_static_world(content, file->content_end, g_opcodes_chars, &length);
	if (!(op = ft_memalloc(sizeof(struct s_libcorewar_opcode_src))))
		return (libcorewar_error("cannot allocate", error, NULL));
	if (*(content + length) == LABEL_CHAR)
	{
		op->label = ft_memcopy(content, length);
		content = libcorewar_state_whitespace(file, content += length + 1, state, error);
		world = ft_static_world(content, file->content_end, g_opcodes_chars, &length);
	}
	hash = ft_hash_src(world, (size_t)length);
	if (!(g_ref = g_opcodes_get + hash)->name || ft_strcmp(g_ref->name, world))
		return (libcorewar_error("unknow opcode", error, NULL));
	content += length;
	return (state_opcode_parameter(file, op, content, error));
}
