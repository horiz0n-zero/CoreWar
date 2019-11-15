/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 09:39:48 by afeuerst          #+#    #+#             */
/*   Updated: 2019/11/15 14:40:34 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static struct s_asm				g_compiler =
{
	.flags = 0,
	.toto = 0,
	.out_directory = NULL
};

static const struct s_argument	g_arguments[256] =
{
	['o'] = {"output-directory", FLAGS_O, 1, &g_compiler.out_directory},
	['d'] = {"decompile", FLAGS_D, 0, NULL}
};

static const char				*g_usages[] =
{
	"usage:\tasm [-od] -- file.s ...\n\n",
	"\t-o --output-directory <file> generate .cor into file directory\n",
	"\t-d --disassemble\n",
	NULL
};

static void					compiler_process_file(const char *const file)
{
	if (g_compiler.flags & FLAGS_D)
	{

	}
}

int							main(int argc, char **argv)
{
	char					*error;

	if (!(argv = arguments_get(++argv, g_arguments, &g_compiler.flags, &error)))
	{
		argv = (char**)g_usages;
		while (*argv)
		{
			write(STDERR_FILENO, *argv, ft_strlen(*argv));
			++argv;
		}
		return (EXIT_FAILURE);
	}
	while (*argv)
		compiler_process_file(*argv++);
	return (EXIT_SUCCESS);
}
