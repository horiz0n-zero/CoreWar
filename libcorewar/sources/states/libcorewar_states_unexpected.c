/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libcorewar_states_unexpected.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 09:40:35 by afeuerst          #+#    #+#             */
/*   Updated: 2019/11/18 09:51:27 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcorewar_get_src_file.h"

char		*libcorewar_state_unexpected(struct s_libcorewar_src_file *const file, char *content, int *const state, char **const error)
{
	if (*state == STATE_HEADER)
		ft_asprintf(error, "unexpected character found in header : %c", *content);
	else
		ft_asprintf(error, "unexpected character found : %c", *content);
	return (content);
}
