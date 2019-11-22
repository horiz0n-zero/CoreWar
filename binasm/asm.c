/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 09:39:48 by afeuerst          #+#    #+#             */
/*   Updated: 2019/11/22 13:15:40 by afeuerst         ###   ########.fr       */
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

static void							print_src_file(struct s_libcorewar_src_file *const file)
{
	struct s_libcorewar_opcode_src	*op;
	int								index;
	static const char				*params[] =
	{
		[T_DIR] = "direct(%d)",
		[T_IND] = "indirect(%d)",
		[T_REG] = "r%d"
	};

	ft_printf("%s %s\n", file->header.prog_name, file->header.comment);
	op = file->opcodes;
	while (op)
	{
		if (op->label)
			ft_printf("\n%s:\t%s", op->label, op->ref->name);
		else
			ft_printf("\t\t%s", op->ref->name);
		index = 0;
		while (index < op->ref->parameters)
		{
			if (!index)
				ft_printf(" ");
			else
				ft_printf(", ");
			if (op->parameters_labels[index])
				ft_printf("%c:%s", '%', op->parameters_labels[index]);
			else
				ft_printf(params[op->parameters_type[index]], op->parameters[index]); 
			++index;
		}
		ft_printf("\n");
		op = op->next;
	}
}

static void							compiler_compile_file(const char *const named)
{
	struct s_libcorewar_src_file	*file;
	int								fd;
	char							*error;

	error = NULL;
	if (!(file = libcorewar_get_src_file(named, &error)))
		ft_dprintf(STDERR_FILENO, "asm: %s: %s\n", named, error);
	else
	{
		if ((fd = open("a.cor", ASMFILE_FLAG, ASMFILE_MODE)) < 0)
			return ((void)ft_dprintf(STDERR_FILENO, "asm: %s: %s\n", named, strerror(errno)));
		libcorewar_out_src_file(fd, file, &error);
		if (error)
			ft_dprintf(STDERR_FILENO, "asm: %s: %s\n", named, error);
		close(fd);
	}
}

static void							compiler_process_file(const char *const named)
{
	struct s_libcorewar_asm_file	*asmfile;
	char							*error;

	error = NULL;
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
		compiler_compile_file(named);
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
