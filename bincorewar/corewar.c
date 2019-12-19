/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 09:40:33 by afeuerst          #+#    #+#             */
/*   Updated: 2019/12/18 09:37:50 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static const char							g_usage[] =
	"usage: corewar [-bealvpq -ds <number> -o <file>] -- [[-n <number>] file.cor ...]\n\n"
	"       -d --dump <number>\n"
	"       run <number> cycles, then dump memory to stdout and exit\n\n"
	"       -s --show <number>\n"
	"       each <number> cycles, dump memory to stdout\n\n"
	"       -o --output <file>\n"
	"       when outputing use file instead of stdout\n"
	"       the file is created and truncated.\n\n"
	"       -b --binary\n"
	"       this option have priority on -e --enable-color\n"
	"       dump memory into binary instead of 32Bytes per line in hexadecimal\n\n"
	"       -e --enable-color\n"
	"       without -b --binary option, champion color ...blabl\n\n"
	"       -a --aff-off\n"
	"       ignore aff instruction\n\n"
	"       -l --live-off\n"
	"       ignore outputing when live instruction executed\n\n"
	"       -v --verbose\n"
	"       display each instruction executed\n\n"
	"       -p --process-info\n"
	"       with -v --verbose display process executing info\n\n"
	"       -q --quiet\n"
	"       set on -a --aff-off and -l --live-off\n"
	"       and remove -v --verbose\n";

struct s_corewar							g_corewar =
{
	0,
	STDOUT_FILENO,
	NULL,
	NULL,
	NULL,
	0,
	0,
	NULL,
	NULL
};

static t_libcorewar_opcode_function			g_functions[256] =
{
	[0x01] = handle_live,
	[0x10] = handle_aff
};

void										corewar_verbosity(void)
{
	if (g_corewar.flags & FLAGS_Q)
	{
		g_corewar.flags |= (FLAGS_A | FLAGS_L);
		g_corewar.flags &= ~(FLAGS_V);
	}
	if (g_corewar.flags & FLAGS_A)
		g_functions[0x10] = NULL;
	if (g_corewar.flags & FLAGS_L)
		g_functions[0x01] = NULL;
	if (g_corewar.flags & FLAGS_V)
	{
		g_functions[0x02] = handle_info;
		g_functions[0x03] = handle_info;
		g_functions[0x04] = handle_info;
		g_functions[0x05] = handle_info;
		g_functions[0x06] = handle_info;
		g_functions[0x07] = handle_info;
		g_functions[0x08] = handle_info;
		g_functions[0x09] = handle_info;
		g_functions[0x0a] = handle_info;
		g_functions[0x0b] = handle_info;
		g_functions[0x0c] = handle_info;
		g_functions[0x0d] = handle_info;
		g_functions[0x0e] = handle_info;
		g_functions[0x0f] = handle_info;
	}
}

void										corewar_loop(void)
{
	t_libcorewar_dump_function				dump;

	if (g_corewar.flags & FLAGS_B)
		dump = libcorewar_dump_binary;
	else if (g_corewar.flags & FLAGS_C)
		dump = libcorewar_dump_colors;
	else
		dump = libcorewar_dump;
	while (libcorewar_arena_cycle(g_corewar.arena))
	{
		if (g_corewar.flags & FLAGS_S && g_corewar.arena->cycles_all && g_corewar.show)
		{
			if (!(g_corewar.arena->cycles_all % g_corewar.show))
				dump(g_corewar.fd, g_corewar.arena);
		}
		if (g_corewar.flags & FLAGS_D && g_corewar.arena->cycles_all && g_corewar.dump)
		{
			if (!(g_corewar.arena->cycles_all % g_corewar.dump))
			{
				dump(g_corewar.fd, g_corewar.arena);
				break ;
			}
		}
	}
}

void										corewar_setup(void)
{
	int										index;

	corewar_verbosity();
	g_corewar.arena = libcorewar_get_arena(g_functions, &g_corewar.error,
			g_corewar.info[0].named, g_corewar.info[0].id,
			g_corewar.info[1].named, g_corewar.info[1].id,
			g_corewar.info[2].named, g_corewar.info[2].id,
			g_corewar.info[3].named, g_corewar.info[3].id, NULL);
	if (g_corewar.error)
	{
		ft_dprintf(STDERR_FILENO, "%s\n", g_corewar.error);
		free(g_corewar.error);
	}
	else
	{
		if (!(g_corewar.flags & FLAGS_Q))
		{
			ft_dprintf(g_corewar.fd, "Introducing contestants...\n");
			index = -1;
			while (++index < g_corewar.arena->champions_count)
				ft_dprintf(g_corewar.fd, "* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
						g_corewar.arena->champions[index].id,
						(int)(g_corewar.arena->champions[index].file->content_size - sizeof(struct s_asm_header)),
						g_corewar.arena->champions[index].file->header->prog_name,
						g_corewar.arena->champions[index].file->header->comment);
		}
		corewar_loop();
	}
	libcorewar_unset_arena(g_corewar.arena);
}

int											main(int argc, char **argv)
{
	char									*error;

	error = NULL;
	arguments_parser(&g_corewar, ++argv);
	if (g_corewar.flags & FLAGS_D && !error)
		g_corewar.dump = ft_atouint32(g_corewar.number_dump, &g_corewar.error);
	else if (g_corewar.flags & FLAGS_S && !error)
		g_corewar.show = ft_atouint32(g_corewar.number_show, &g_corewar.error);
	else if (g_corewar.flags & FLAGS_O && !error)
		if ((g_corewar.fd = open(g_corewar.file_output, COF, COM)) < 0)
			ft_asprintf(&g_corewar.error, "%s: %s", g_corewar.file_output, strerror(errno));
	if (!g_corewar.info_count || error)
	{
		if (error)
		{
			ft_dprintf(STDERR_FILENO, "%s\n%s", error, g_usage);
			free(error);
		}
		else
			write(STDERR_FILENO, g_usage, sizeof(g_usage));
		return (EXIT_FAILURE);
	}
	else
		corewar_setup();
	return (EXIT_SUCCESS);
}
