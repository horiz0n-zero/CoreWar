/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 10:54:34 by afeuerst          #+#    #+#             */
/*   Updated: 2019/12/09 14:56:22 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcorewar_arena_cycle.h"

void	cycle_live(struct s_libcorewar_arena *const arena, struct s_libcorewar_process *const process)
{
	int	index;

	process->isalive = 1;
	++process->lives_count;
	index = 0;
	while (index < arena->champions_count)
	{
		if (arena->champions[index].id == process->opcode_data.params[0])
		{
			arena->liveid = arena->champions[index].id;
			break ;
		}
		++index;
	}
}
