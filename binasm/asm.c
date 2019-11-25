/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 09:39:48 by afeuerst          #+#    #+#             */
/*   Updated: 2019/11/25 09:30:16 by afeuerst         ###   ########.fr       */
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
	['h'] = {"hexcolors", FLAGS_H, 0, NULL},
	['l'] = {"labels", FLAGS_L, 0, NULL},
	['c'] = {"compile", FLAGS_C, 0, NULL}
};

static const char					*g_usages[] =
{
	"usage: asm [-dhlc] [-p <prefix>] -- [file ...]\n\n",
	"       -h --hexcolors\n",
	"          disassemble .cor files and show their instructions\n",
	"          each line contain one instruction with the following format:\n",
	"          addr opcode_name opcode_value [ parameters ]\n\n",
	"       -d --disassemble\n",
	"          disassemble .cor files into readable .s files\n",
	"          this option override -h --hexcolors\n\n",
	"       -l --labels\n",
	"          when dissasembling with option -d --disassemble\n",
	"          try to resolve labels instead of showing direct integer value\n\n",
	"       -p --prefix <prefix>\n",
	"          when -d --disassemble with option -l --labels is set\n"
	"          each resolve labels will be named :<prefix>x instead of :label_x\n\n",
	"       -c --compile\n",
	"          transform .s files into .cor files\n",
	"          files are saved at the same location of .s replacing suffix .s by .cor\n",
	"          if suffix .s is not specified and is a valid file, .cor is appended\n"
	"          this option is enabled by default\n",
	"          this option cannot override -d --disassemble or -h --hexcolors\n",
	NULL
};

static void							compiler_compile_file(const char *const named, const int multi)
{
	struct s_libcorewar_src_file	*file;
	int								fd;
	char							*error;
	static const char *const		target = "a.cor";

	error = NULL;
	file = libcorewar_get_src_file(named, &error);
	if (error)
		ft_dprintf(STDERR_FILENO, "asm: %s: %s\n", named, error);
	else
	{
		if ((fd = open(target, ASMFILE_FLAG, ASMFILE_MODE)) < 0)
			return ((void)ft_dprintf(STDERR_FILENO, "asm: %s: %s\n", named, strerror(errno)));
		libcorewar_bswap_src_file(file);
		libcorewar_out_src_file(fd, file, &error);
		if (error)
			ft_dprintf(STDERR_FILENO, "asm: %s: %s\n", named, error);
		else
			ft_printf("Writing output program to %s\n", target);
		close(fd);
	}
	libcorewar_unset_src_file(file);
	if (error)
		free(error);
}

static void							compiler_hexcolors_file(const char *const named, const int multi)
{
	struct s_libcorewar_asm_file	*file;
	char							*error;

	if (!(file = libcorewar_get_asm_file(named, &error, g_compiler.prefix)))
		ft_dprintf(STDERR_FILENO, "asm: %s: %s\n", named, error); // free error
	else
	{
		if (multi)
			ft_printf("%s:\n", named);
		libcorewar_bswap_asm_file(file);
		libcorewar_out_asm_file_hexcolors(STDOUT_FILENO, file);
	}
}

static void							compiler_decompile_file(const char *const named, const int multi)
{
	struct s_libcorewar_asm_file	*file;
	char							*error;

	error = NULL;
	file = libcorewar_get_asm_file(named, &error, g_compiler.prefix);
	if (error)
	{
		ft_dprintf(STDERR_FILENO, "asm: %s: %s\n", named, error);
		free(error);
	}
	else
	{
		if (multi)
			ft_printf("%s:\n", named);
		libcorewar_out_asm_file(STDOUT_FILENO, file);
	}
	libcorewar_unset_asm_file(file);
}

int									main(int argc, char **argv)
{
	char							*error;
	t_asm_file_func					func;
	int								multi;

	if (!(argv = arguments_get(++argv, g_arguments, &g_compiler.flags, &error)))
	{
		ft_dprintf(STDERR_FILENO, "%s\n", error);
		argv = (char**)g_usages;
		while (*argv)
			ft_dprintf(STDERR_FILENO, "%s", *argv++);
		return (EXIT_FAILURE);
	}
	if (g_compiler.flags & FLAGS_D)
		func = compiler_decompile_file;
	else if (g_compiler.flags & FLAGS_H)
		func = compiler_hexcolors_file;
	else
		func = compiler_compile_file;
	if (*argv && *(argv + 1))
		multi = 1;
	else
		multi = 0;
	if (g_compiler.flags & FLAGS_L && !(g_compiler.flags & FLAGS_P))
		g_compiler.prefix = "label_";
	while (*argv)
		func(*argv++, multi);
	return (EXIT_SUCCESS);
}
