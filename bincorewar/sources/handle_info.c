/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 09:54:00 by afeuerst          #+#    #+#             */
/*   Updated: 2019/12/13 14:54:43 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	handle_info(struct s_libcorewar_arena *const arena, struct s_libcorewar_process *const process)
{
	int	index;

	ft_dprintf(g_corewar.fd, "%s ", process->opcode_data.info->name);
	index = 0;
	while (index < process->opcode_data.info->parameters)
	{
		if (process->opcode_data.types[index] & T_REG)
			ft_dprintf(g_corewar.fd, "r%u ", process->opcode_data.params[index]);
		else
			ft_dprintf(g_corewar.fd, "%u ", process->opcode_data.params[index]);
		++index;
	}
	ft_dprintf(g_corewar.fd, "\n");
}
