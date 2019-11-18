/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libcorewar_get_src_file.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 11:47:27 by afeuerst          #+#    #+#             */
/*   Updated: 2019/11/18 15:24:22 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcorewar_get_src_file.h"

static const t_state_func							g_state_header[256] =
{
	[0 ... 255] = libcorewar_state_unexpected,
	['.'] = libcorewar_state_head_point,
	[' '] = libcorewar_state_whitespace,
	['\t'] = libcorewar_state_whitespace,
	['\n'] = libcorewar_state_whitespace,
	['#'] = libcorewar_state_comment
};

static const t_state_func							g_state_opcode[256] =
{
	[0 ... 255] = libcorewar_state_unexpected,
	[' '] = libcorewar_state_whitespace,
	['\t'] = libcorewar_state_whitespace,
	['\n'] = libcorewar_state_whitespace,
	['#'] = libcorewar_state_comment,
	['a' ... 'z'] = libcorewar_state_opcode,
	['0' ... '9'] = libcorewar_state_opcode,
	['_'] = libcorewar_state_opcode
};

static const t_state_func							*g_state[2] =
{
	[STATE_HEADER] = g_state_header,
	[STATE_OPCODE] = g_state_opcode
};

static void											libcorewar_get_src_loop(struct s_libcorewar_src_file *const file, char **const error)
{
	char											*content;
	int												state;

	state = 0;
	content = file->content;
	*error = NULL;
	while (content < file->content_end)
	{
		content = g_state[state][(int)*content & 0xFF](file, content, &state, error);
		if (*error)
			break ;
	}
}

struct s_libcorewar_src_file						*libcorewar_get_src_file(const char *const named, char **const error)
{
	const int										fd = open(named, O_RDONLY);
	struct s_libcorewar_src_file					*file;

	if (!(file = ft_memalloc(sizeof(struct s_libcorewar_src_file))))
		return (libcorewar_error("cannot allocate", error, NULL));
	if (fd < 0)
		return (libcorewar_error("cannot open", error, file, NULL));
	if (fstat(fd, &file->content_stat) < 0)
		return (libcorewar_error("cannot fstat", error, file, NULL));
	if ((file->content = mmap(NULL, file->content_stat.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (libcorewar_error("cannot mmap", error, file, NULL));
	file->content_end = file->content + file->content_stat.st_size;
	libcorewar_get_src_loop(file, error);
	if (*error)
		return (NULL);
	return (file);
}
