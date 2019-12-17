/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 11:31:33 by afeuerst          #+#    #+#             */
/*   Updated: 2019/12/13 13:31:45 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arguments_parser.h"

static const struct s_argument		g_arguments[256] =
{
	['d'] = {"dump", FLAGS_D, 1, &g_corewar.number_dump},
	['s'] = {"show", FLAGS_S, 1, &g_corewar.number_show},
	['o'] = {"output", FLAGS_O, 1, &g_corewar.file_output},
	['b'] = {"binary", FLAGS_B, 0, NULL},
	['e'] = {"enable-color", FLAGS_C, 0, NULL},
	['a'] = {"aff-off", FLAGS_A, 0, NULL},
	['l'] = {"live-off", FLAGS_L, 0, NULL},
	['v'] = {"verbose", FLAGS_V, 0, NULL},
	['p'] = {"process-info", FLAGS_P, 0, NULL},
	['q'] = {"quiet", FLAGS_Q, 0, NULL}
};

static const struct s_chargument	g_champions_args[256] =
{
	['n'] = {"number", champion_arg_id},
	['c'] = {"color", champion_arg_color}
};

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
		if (g_champions_args[(int)*ptr & 0xFF].named && *(ptr - 1) == '-' && !*(ptr + 1))
		{
			*champi = 1;
			return (argv);
		}
		arg = g_arguments + (int)*ptr++;
		if (!arg->name && ft_asprintf(error, "illegal option -- %c", error, ptr[-1]))
			return (NULL);
		*flags |= arg->flags;
		if (arg->require)
		{
			if (!*argv && ft_asprintf(error, "option requires an argument -- %c", ptr[-1]))
				return (NULL);
			else
				*arg->required = *argv++;
		}
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
	const struct s_argument			*arg = g_arguments + (int)*name;

	if (!arg->name && !ft_strcmp(g_champions_args[(int)*name].named, name))
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

static void							arguments_champions(struct s_corewar *const corewar, char **argv)
{
	const struct s_chargument		*arg;

	while (!corewar->error && *argv)
	{
		if (**argv == '-')
		{
			if (!(arg = g_champions_args + *((*argv) + 1))->named)
				arg = g_champions_args + *(*argv + 2);
			if (!*++argv)
				return ((void)ft_asprintf(&corewar->error, "champion option requires an argument -%c --%s", arg->named[0], arg->named));
			arg->func(corewar, *argv++);
		}
		else
		{
			if (corewar->info_count + 1 > MAX_PLAYERS)
				return ((void)ft_asprintf(&corewar->error, "max players"));
			if (!(corewar->info[corewar->info_count].flags & FLAGS_CHAMPION_N))
				champion_arg_id(corewar, NULL);
			if (!(corewar->info[corewar->info_count].flags & FLAGS_CHAMPION_C))
				champion_arg_color(corewar, NULL);
			corewar->info[corewar->info_count].named = *argv++;
			++corewar->info_count;
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
				argv = argument_long(argv, &corewar->flags, &champi, &corewar->error);
			}
			else
				argv = argument_short(argv, &corewar->flags, &champi, &corewar->error);
		}
		else
			break ;
	}
	arguments_champions(corewar, argv);
}
