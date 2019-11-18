/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libcorewar_states_header.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 10:44:18 by afeuerst          #+#    #+#             */
/*   Updated: 2019/11/18 14:19:59 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcorewar_get_src_file.h"
#include <stddef.h>

static const char								g_hquotes[256] =
{
	['\"'] = '\"',
	['\''] = '\'',
	['`'] = '`'
};

static const struct s_libcorewar_head_point		g_ref_head_points[] =
{
	{
		NAME_CMD_STRING,
		GETTED_NAME,
		offsetof(struct s_libcorewar_src_file, header.prog_name),
		PROG_NAME_LENGTH
	},
	{
		COMMENT_CMD_STRING,
		GETTED_COMM,
		offsetof(struct s_libcorewar_src_file, header.comment),
		COMMENT_LENGTH
	}
};

static char										*state_fill(struct s_libcorewar_src_file *const file,
		const int head, char *content, char **const error)
{
	const struct s_libcorewar_head_point *const	ref = g_ref_head_points + head;
	const char									*ptr_end;
	char										*ptr;
	char										quote;

	ptr = ref->name + 1;
	while (content < file->content_end && *ptr && *ptr == *content)
	{
		++content;
		++ptr;
	}
	if (*ptr && ft_asprintf(error, "did you mean %s ?", ref->name))
		return (content);
	ptr = ((char*)file) + ref->file_offset;
	ptr_end = ptr + ref->file_length;
	content = libcorewar_state_whitespace(file, content, NULL, error);
	if (!(quote = g_hquotes[(int)*content++ & 0xFF]) && ft_asprintf(error, "bad quote %c", *(content - 1)))
		return (content);
	while (content < file->content_end && *content != quote && ptr < ptr_end)
		*ptr++ = *content++;
	if (*content != quote && ptr < ptr_end)
		ft_asprintf(error, "no terminating quote");
	else if (*content != quote && ptr >= ptr_end)
		ft_asprintf(error, "length too long");
	else if (*(content - 1) == quote)
		ft_asprintf(error, "cannot be empty");
	return (++content);
}

char				*libcorewar_state_head_point(struct s_libcorewar_src_file *const file, char *content, int *const state, char **const error)
{
	static size_t	getted = 0;
	int				index;
	char *const		start = ++content;

	index = 0;
	while (!*error && index < sizeof(g_ref_head_points) / sizeof(g_ref_head_points[0]))
	{
		if (*content == g_ref_head_points[index].name[1])
		{
			if (getted & g_ref_head_points[index].getted && !(getted = 0))
				ft_asprintf(error, "%s cannot be redefined", g_ref_head_points[index].name);
			else
			{
				content = state_fill(file, index, content, error);
				getted |= g_ref_head_points[index].getted;
			}
		}
		++index;
	}
	if (!*error && start == content && !(getted = 0))
		ft_asprintf(error, "unknow head points");
	if (getted == GETTED_ALL && !(getted = 0))
		*state = STATE_OPCODE;
	return (content);
}
















