/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_live.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 09:35:58 by afeuerst          #+#    #+#             */
/*   Updated: 2019/12/14 12:09:37 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	handle_live(struct s_libcorewar_arena *const arena, struct s_libcorewar_process *const process)
{
	int	index;

	index = 0;
	while (index < arena->champions_count)
	{
		if (arena->champions[index].id == (int32_t)process->r[0])
		{
			ft_dprintf(g_corewar.fd, "un processus dit que le joueur %u(%s) est en vie\n", arena->champions[index].id, arena->champions[index].name);
			break ;
		}
		++index;
	}
}
