/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 11:31:33 by afeuerst          #+#    #+#             */
/*   Updated: 2019/12/06 15:30:28 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arguments_parser.h"

static const struct s_argument		g_arguments[256] =
{
	['d'] = {"dump", FLAGS_D, 1, &g_corewar.number_dump},
	['s'] = {"show", FLAGS_S, 1, &g_compiler.number_show},
	['o'] = {"output", FLAGS_O, 1, &g_compiler.file_output},
	['b'] = {"binary", FLAGS_B, 0, NULL},
	['e'] = {"enable-color", FLAGS_C, 0, NULL},
	['a'] = {"aff-off", FLAGS_A, 0, NULL},
	['l'] = {"live-off", FLAGS_L, 0, NULL},
	['v'] = {"verbose", FLAGS_V, 0, NULL},
	['p'] = {"process-info", FLAGS_P, 0, NULL},
	['q'] = {"quiet", FLAGS_Q, 0, NULL}
};

static const char					g_n = 'n';
static const char					*g_number = "number";

static char							**argument_short(
		char **argv,
		int *const flags,
		int *const champi,
		char **const error)
{
	const char						*ptr;
	const struct s_argument			*arg;

	ptr = *argv++ + 1;
	while (*ptr)
	{
		if (*ptr == g_n && *(ptr - 1) == '-' && !*(ptr + 1))
		{
			*champi = 1;
			return (argv);
		}
		arg = g_arguments + (int)*ptr++;
		if (!arg->name && ft_asprintf(error, "illegal option -- %c", error, ptr[-1]))
			return (NULL);
		*flags |= arg->flags;
		if (arg->require)
			if (!*argv && ft_asprintf(error, "option requires an argument -- %c", ptr[-1]))
				return (NULL);
			else
				*arg->required = *argv++;
	}
	return (argv);
}

static char							**argument_long(
		char **argv,
		int *const flags,
		int *const champi,
		char **const error)
{
	const char						*name = *argv++ + 2;
	const struct s_argument			*arg = arguments + (int)*name;

	if (!arg->name && !ft_strcmp(name, g_number))
	{
		*champi = 1;
		return (argv);
	}
	if (!arg->name || (ft_strcmp(arg->name, name) && ft_asprintf(error, "illegal option --%s", name)))
		return (NULL);
	*flags |= arg->flags;
	if (arg->require)
	{
		if (!*argv && ft_asprintf(error, "option requires an argument --%s", name))
			return (NULL);
		else
			*arg->required = *argv++;
	}
	return (argv);
}

static void							arguments_id_exist(struct s_corewar *const corewar, const int id)
{
	int								index;

	index = 0;
	while (index < corewar->info_count)
	{
		if (corewar->info[index].id == id)
		{
			ft_asprintf(&corewar->error, "champion cannot have the same id");
		}
		++index;
	}
}

static void							arguments_champions(struct s_corewar *const corewar, char **argv)
{
	int								id;

	id = 0;
	while (!corewar->error && *argv)
	{
		if (**argv == '-')
		{
			if (!*++argv)
				return ((void)ft_asprintf(&corewar->error, "option requires an argument -n --number"));
			id = ft_atouint32(*argv++, &corewar->error);
			arguments_id_exist(corewar, id);
		}
		else
		{
			if (corewar->info_count + 1 >= MAX_PLAYERS)
				return ((void)ft_asprintf(&corewar->error, "max players"));
			arguments_id_exist(corewar, id);
			if (corewar->error)
				break ;
			corewar->info[corewar->info_count].named = *argv++;
			corewar->info[corewar->info_count++].id = id++;
		}
	}
}

void								arguments_parser(struct s_corewar *const corewar, char **argv)
{
	int								champi;

	champi = 0;
	while (!champi && argv && *argv)
	{
		if (**argv == '-')
		{
			if (!*(*argv + 1))
				break ;
			else if (*(*argv + 1) == '-')
			{
				if (!*(*argv + 2) && ++argv)
					break ;
				argv = argument_long(argv, &champi, &corewar->flags, &corewar->error);
			}
			else
				argv = argument_short(argv, &champi, &corewar->flags, &corewar->error);
		}
		else
			break ;
	}
	arguments_champions(corewar, argv);
}
