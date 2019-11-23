/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libcorewar_out_asm_file.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 13:35:19 by afeuerst          #+#    #+#             */
/*   Updated: 2019/11/23 14:16:11 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcorewar.h"

static void							out_asm_file_opcode(const int fd, struct s_libcorewar_opcode_get *const op)
{
	int								index;

	index = 0;
	if (op->label)
		ft_dprintf(fd, "%s: %s ", op->label, op->ref->name);
	else
		ft_dprintf(fd, "\t%s ", op->ref->name);
	while (index < op->ref->parameters)
	{
		if (op->parameters_type[index] == REG_CODE)
			ft_dprintf(fd, "r%hhu", (unsigned char)op->parameters[index]);
		else if (op->parameters_type[index] == IND_CODE)
			ft_dprintf(fd, "%hu", (unsigned short)op->parameters[index]);
		else
		{
			if (op->parameters_labels[index])
				ft_dprintf(fd, "%%:%s", op->parameters_labels[index]);
			else
				ft_dprintf(fd, "%%%u", op->parameters[index]);
		}
		if (++index < op->ref->parameters)
			ft_dprintf(fd, ", ");
	}
	write(fd, "\n", 1);
}

void								libcorewar_out_asm_file(const int fd, struct s_libcorewar_asm_file *const file)
{
	struct s_libcorewar_opcode_get	*op;

	ft_dprintf(fd, "#\n# generated by libcorewar\n#\n\n");
	ft_dprintf(fd, "%s \"%s\"\n", NAME_CMD_STRING, file->header->prog_name);
	ft_dprintf(fd, "%s \"%s\"\n\n", COMMENT_CMD_STRING, file->header->comment);
	op = file->opcodes;
	while (op)
	{
		out_asm_file_opcode(fd, op);
		op = op->next;
	}
}

static void							out_asm_file_opcode_hexcolors(const int fd, struct s_libcorewar_asm_file *const file,
		struct s_libcorewar_opcode_get *const op)
{
	int								index;

	index = 0;
	ft_dprintf(fd, "\033[0m%#08x \033[38:5:211m%5s  %02hhx ", op->start - file->content, op->ref->name, op->ref->opvalue);
	if (op->ref->parameters_encoding)
		ft_dprintf(fd, "\033[38:5:209m%02hhx ", libcorewar_opcode_get_encoded_parameters(op));
	while (index < op->ref->parameters)
	{
		if (op->parameters_type[index] == REG_CODE)
			ft_dprintf(fd, "\033[38:5:123m%02hhx", op->parameters[index]);
		else if (op->parameters_type[index] == IND_CODE)
			ft_dprintf(fd, "\033[38:5:157m%02hh[2 ]x", op->parameters + index);
		else
		{
			if (op->ref->parameters_direct_small)
				ft_dprintf(fd, "\033[38:5:229m%02hh[2 ]x", op->parameters + index);
			else
				ft_dprintf(fd, "\033[38:5:229m%02hh[4 ]x", op->parameters + index);
		}
		if (++index < op->ref->parameters)
			ft_dprintf(fd, " ");
	}
	write(fd, "\033[0m\n", sizeof("\033[0m\n"));
}

void								libcorewar_out_asm_file_hexcolors(const int fd, struct s_libcorewar_asm_file *const file)
{
	struct s_libcorewar_opcode_get	*op;

	op = file->opcodes;
	while (op)
	{
		out_asm_file_opcode_hexcolors(fd, file, op);
		op = op->next;
	}
}
