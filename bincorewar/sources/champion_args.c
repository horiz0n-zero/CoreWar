/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champion_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 10:47:01 by afeuerst          #+#    #+#             */
/*   Updated: 2019/12/14 11:35:17 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void			arg_color_duplicate(struct s_corewar *const corewar, const unsigned char colorid)
{
	int				index;

	index = 0;
	while (index < corewar->info_count - 1)
	{
		if (corewar->info[index].colorid == colorid)
		{
			ft_asprintf(&corewar->error, "duplicated champion %scolor\033[0m", libcorewar_color(colorid));
			break ;
		}
		++index;
	}
}

void				champion_arg_color(struct s_corewar *const corewar, const char *arg)
{
	if (!arg)
	{
		if (corewar->info_count && corewar->info[corewar->info_count - 1].flags & FLAGS_CHAMPION_C)
			corewar->info[corewar->info_count].colorid = libcorewar_colorid_nextid(corewar->info[corewar->info_count - 1].colorid);
		else
			corewar->info[corewar->info_count].colorid = libcorewar_colorid_next();
		arg_color_duplicate(corewar, corewar->info[corewar->info_count].colorid);
	}
	else
	{
		corewar[corewar->info_count].flags |= FLAGS_CHAMPION_N;
		corewar->info[corewar->info_count].colorid = libcorewar_colorid(arg);
		arg_color_duplicate(corewar, corewar->info[corewar->info_count].colorid);
	}
}

static void			arg_id_duplicate(struct s_corewar *const corewar, const int id)
{
	int				index;

	index = 0;
	while (index < corewar->info_count - 1)
	{
		if (corewar->info[index].id == (uint32_t)id)
		{
			ft_asprintf(&corewar->error, "duplicated champion id %d", id);
			break ;
		}
		++index;
	}
}

void				champion_arg_id(struct s_corewar *const corewar, const char *arg)
{
	static uint32_t	id = 0;

	if (!arg)
	{
		if (corewar->info_count && corewar->info[corewar->info_count - 1].flags & FLAGS_CHAMPION_N)
			id = corewar->info[corewar->info_count - 1].id + 1;
		corewar->info[corewar->info_count].id = id;
		arg_id_duplicate(corewar, id++);
	}
	else
	{
		id = ft_atouint32(arg, &corewar->error);
		corewar[corewar->info_count].flags |= FLAGS_CHAMPION_N;
		corewar->info[corewar->info_count].id = id;
		arg_id_duplicate(corewar, id++);
	}
}
