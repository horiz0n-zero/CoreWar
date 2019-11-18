/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 09:39:48 by afeuerst          #+#    #+#             */
/*   Updated: 2019/11/18 10:00:41 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static struct s_asm					g_compiler =
{
	.flags = 0,
	.pad = 0,
	.prefix = NULL
};

static const struct s_argument		g_arguments[256] =
{
	['d'] = {"disassemble", FLAGS_D, 0, NULL},
	['p'] = {"prefix", FLAGS_P, 1, &g_compiler.prefix},
	['h'] = {"hexcolors", FLAGS_H, 0, NULL}
};

static const char					*g_usages[] =
{
	"usage:\tasm [-d] [-p <prefix>] -- file ...\n\n",
	"\t-d --disassemble transform .cor into readable .s file\n",
	"\t\t-p --prefix <prefix> each labels will be named :<prefix>x instead of :label_x\n",
	"\t\t-h --hexcolors out the file in colored\n",
	NULL
};

static void							compiler_process_file(const char *const named)
{
	struct s_libcorewar_asm_file	*asmfile;
	struct s_libcorewar_src_file	*srcfile;
	char							*error;

	if (g_compiler.flags & FLAGS_D)
	{
		if ((asmfile = libcorewar_get_asm_file(named, &error, g_compiler.prefix)))
			if (g_compiler.flags & FLAGS_H)
				libcorewar_out_asm_file_hexcolors(STDOUT_FILENO, asmfile);
			else
				libcorewar_out_asm_file(STDOUT_FILENO, asmfile);
		else
			ft_dprintf(STDERR_FILENO, "asm: %s: %s\n", named, error);
	}
	else
	{
		if (!(srcfile = libcorewar_get_src_file(named, &error)))
			ft_dprintf(STDERR_FILENO, "asm: %s: %s\n", named, error);
	}
}

int									main(int argc, char **argv)
{
	char							*error;

	if (!(argv = arguments_get(++argv, g_arguments, &g_compiler.flags, &error)))
	{
		ft_dprintf(STDERR_FILENO, "%s\n", error);
		argv = (char**)g_usages;
		while (*argv)
			ft_dprintf(STDERR_FILENO, "%s", *argv++);
		return (EXIT_FAILURE);
	}
	while (*argv)
		compiler_process_file(*argv++);
	return (EXIT_SUCCESS);
}
