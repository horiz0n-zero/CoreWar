/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 09:10:05 by afeuerst          #+#    #+#             */
/*   Updated: 2019/12/09 14:36:34 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcorewar_arena_cycle.h"

void	cycle_st(struct s_libcorewar_arena *const arena, struct s_libcorewar_process *const process,
		const int *const types, const int *const params)
{
	if (process->opcode_data.types[1] & T_REG)
		process->r[process->opcode_data.params[0]] = process->r[process->opcode_data.params[1]];
	else
		process->r[process->opcode_data.params[0]] = process->opcode_data.params[1] % IDX_MOD;
}
