/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libcorewar_states_skip.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 09:34:47 by afeuerst          #+#    #+#             */
/*   Updated: 2019/11/18 10:43:41 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcorewar_get_src_file.h"

static const int	g_whitespace[256] =
{
	[' '] = 1,
	['\t'] = 1,
	['\n'] = 1
};

char				*libcorewar_state_whitespace(struct s_libcorewar_src_file *const file, char *content, int *const state, char **const error)
{
	while (content < file->content_end && g_whitespace[(int)*content & 0xFF])
	{
		++content;
	}
	return (content);
}

char				*libcorewar_state_comment(struct s_libcorewar_src_file *const file, char *content, int *const state, char **const error)
{
	while (content < file->content_end && *content != '\n')
	{
		++content;
	}
	if (*content == '\n')
		return (++content);
	return (content);
}
