/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 13:36:04 by afeuerst          #+#    #+#             */
/*   Updated: 2019/12/13 13:51:24 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dump.h"

void				corewar_dump_binary(void)
{
	write(g_corewar.fd, g_corewar.arena->memory, MEM_SIZE);
}

void				corewar_dump_colors(void)
{
	int				index;
	int				pos;
	const char		*ptr;
	unsigned char	*color;
	unsigned char	colorid;

	index = 0;
	while (index < LINES)
	{
		pos = 0;
		while (pos < BYTES_LINE)
		{
			ptr = g_corewar.arena->memory + (index * BYTES_LINE) + pos;
			color = g_corewar.arena->colorsid + (index * BYTES_LINE) + pos;
			colorid = *color;
			while (pos < BYTES_LINE && colorid == *(color + pos))
				++pos;
			if (pos < BYTES_LINE)
				ft_dprintf(g_corewar.fd, "%s%#04hh[* ]x", libcorewar_color(colorid), pos + 1, ptr);
			else
				ft_dprintf(g_corewar.fd, "%s%#04hh[* ]x\n", libcorewar_color(colorid), pos + 1, ptr);
		}
		++index;
	}
	ft_dprintf(g_corewar.fd, "\n");
}

void				corewar_dump(void)
{
	int				index;
	char			*ptr;

	ptr = g_corewar.arena->memory;
	index = 0;
	while (index < LINES)
	{
		ft_dprintf(g_corewar.fd, "%#04hh[* ]x\n", BYTES_LINE, ptr);
		ptr += BYTES_LINE;
		++index;
	}
	ft_dprintf(g_corewar.fd, "\n");
}
