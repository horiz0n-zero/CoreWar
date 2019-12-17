/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_aff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 09:43:26 by afeuerst          #+#    #+#             */
/*   Updated: 2019/12/12 14:10:40 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	handle_aff(struct s_libcorewar_arena *const arena, struct s_libcorewar_process *const process)
{
	ft_dprintf(g_corewar.fd, "aff: %d\n", process->opcode_data.params[0]);
}
