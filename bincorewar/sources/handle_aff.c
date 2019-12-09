/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_aff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 09:43:26 by afeuerst          #+#    #+#             */
/*   Updated: 2019/12/03 09:53:55 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	handle_aff(struct s_libcorewar_arena *const arena, struct s_libcorewar_process *const process, const int *const types, const int *const params)
{
	ft_dprintf(g_corewar.fd, "aff: %d\n", params[0]);
}
