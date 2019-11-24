/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libcorewar_encoded_parameters.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 10:46:25 by afeuerst          #+#    #+#             */
/*   Updated: 2019/11/24 16:25:54 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcorewar_encoded_parameters.h"

static const char	g_opcode_encoded[] =
{
	[T_DIR] = DIR_CODE,
	[T_IND] = IND_CODE,
	[T_REG] = REG_CODE
};

char				libcorewar_opcode_src_encoded_parameters(struct s_libcorewar_opcode_src *const op)
{
	char			r;
	int				index;

	index = 0;
	r = 0;
	while (index < op->ref->parameters)
	{
		r |= g_opcode_encoded[op->parameters_type[index]];
		if (++index < op->ref->parameters)
			r <<= 2;
	}
	index = MAX_ARGS_NUMBER - index;
	if (index > 0)
		r <<= 2 * index;
	return (r);
}

char				libcorewar_opcode_get_encoded_parameters(struct s_libcorewar_opcode_asm *const op)
{
	char			r;
	int				index;

	index = 0;
	r = 0;
	while (index < op->ref->parameters)
	{
		r |= g_opcode_encoded[op->parameters_type[index]];
		if (++index < op->ref->parameters)
			r <<= 2;
	}
	index = MAX_ARGS_NUMBER - index;
	if (index > 0)
		r <<= 2 * index;
	return (r);
}
