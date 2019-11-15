/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 09:40:33 by afeuerst          #+#    #+#             */
/*   Updated: 2019/11/15 12:57:03 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdio.h>

void		print_file(struct s_libcorewar_asm_file *const file)
{
	printf("%s %s\n", file->header->prog_name, file->header->comment);
	printf("%d %lld\n", file->header->prog_size, file->content_stat.st_size);
}

int			main(int argc, char **argv)
{
	char	*error;
	struct s_libcorewar_asm_file	*file;

	while (*++argv)
	{
		if (!(file = libcorewar_get_asm_file(*argv, &error)))
		{
			printf("%s\n", error);
		}
		else
			print_file(file);
	}
}






















