/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 12:40:29 by afeuerst          #+#    #+#             */
/*   Updated: 2019/12/09 14:53:01 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcorewar_arena_cycle.h"

void	cycle_sti(struct s_libcorewar_arena *const arena, struct s_libcorewar_process *const process, const int *const types, const int *const params)
{
	uint32_t	p1;
	uint32_t	p2;

	if (process->opcode_data.types[1] & T_REG)
		p1 = process->r[process->opcode_data.params[1]];
	else
		p1 = process->opcode_data.params[1];
	if (process->opcode_data.types[2] & T_REG)
		p1 = process->r[process->opcode_data.params[2]];
	else
		p1 = process->opcode_data.params[2];
	process->r[process->opcode_data.params[0]] = (p1 + p2) % IDX_MOD;
}
