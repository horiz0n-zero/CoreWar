/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libcorewar_out_src_file.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 11:33:19 by afeuerst          #+#    #+#             */
/*   Updated: 2019/11/22 14:32:51 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcorewar_out_src_file.h"

static char							out_opcode_encoding_parameters(struct s_libcorewar_opcode_src *const op)
{
	char							r;
	int								index;
	static const char				opcode_encoded[] =
	{
		[T_DIR] = DIR_CODE,
		[T_IND] = IND_CODE,
		[T_REG] = REG_CODE
	};

	index = 0;
	r = 0;
	while (index < op->ref->parameters)
	{
		r |= opcode_encoded[op->parameters_type[index]];
		if (++index < op->ref->parameters)
			r <<= 2;
	}
	index = MAX_ARGS_NUMBER - index;
	if (index > 0)
		r <<= 2 * index;
	return (r);
}

static char							*out_opcodes(struct s_libcorewar_src_file *const file, char *ins)
{
	struct s_libcorewar_opcode_src	*op;
	int								index;
	static const int				opcodes_parameters_size[] =
	{
		[T_DIR] = DIR_SIZE,
		[T_IND] = IND_SIZE,
		[T_REG] = REG_SIZE
	};

	op = file->opcodes;
	while (op)
	{
		*ins++ = (char)op->ref->opvalue;
		if (op->ref->parameters_encoding)
			*ins++ = out_opcode_encoding_parameters(op);
		index = 0;
		while (index < op->ref->parameters)
		{
			if (op->parameters_type[index] & T_REG)
				*ins = (char)op->parameters[index];
			else if (op->parameters_type[index] & T_IND)
				*(short*)ins = __builtin_bswap16((short)op->parameters[index]);
			else
				*(int*)ins = __builtin_bswap32((int)op->parameters[index]);
			ins += opcodes_parameters_size[op->parameters_type[index]];
			++index;
		}
		op = op->next;
	}
	return (ins);
}

void								libcorewar_out_src_file(const int fd, struct s_libcorewar_src_file *const file, char **const error)
{
	char							ins[file->opcodes_count * MAX_OPCODE_SIZE];
	size_t							ins_length;

	ins_length = (size_t)(out_opcodes(file, ins) - ins);
	file->header.magic = __builtin_bswap32(COREWAR_EXEC_MAGIC);
	file->header.prog_size = __builtin_bswap32((int)ins_length);
	if ((write(fd, &file->header, sizeof(struct s_asm_header))) == -1)
		return (strerror_void(error));
	if ((write(fd, ins, ins_length)) == -1)
		return (strerror_void(error));
}
