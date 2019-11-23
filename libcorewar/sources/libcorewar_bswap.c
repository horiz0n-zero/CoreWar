/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libcorewar_bswap.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 13:17:59 by afeuerst          #+#    #+#             */
/*   Updated: 2019/11/23 13:54:30 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcorewar_bswap.h"

void								libcorewar_bswap_asm_file(struct s_libcorewar_asm_file *const file)
{
	struct s_libcorewar_opcode_get	*op;
	int								p;

	op = file->opcodes;
	file->header->magic = __builtin_bswap32(file->header->magic);
	file->header->prog_size = __builtin_bswap32(file->header->prog_size);
	while (op)
	{
		p = 0;
		while (p < op->ref->parameters)
		{
			if (op->parameters_type[p] == T_IND)
				op->parameters[p] = (int)__builtin_bswap16((short)op->parameters[p]);
			else if (op->parameters_type[p] == T_DIR)
			{
				if (op->ref->parameters_direct_small)
					op->parameters[p] = (int)__builtin_bswap16((short)op->parameters[p]);
				else
					op->parameters[p] = __builtin_bswap32(op->parameters[p]);
			}
			++p;
		}
		op = op->next;
	}
}
