/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 09:39:29 by afeuerst          #+#    #+#             */
/*   Updated: 2019/11/22 11:37:01 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "libcorewar.h"

# define FLAGS_D 1 << 0
# define FLAGS_P 1 << 1
# define FLAGS_H 1 << 2

struct			s_asm
{
	int			flags;
	int			pad;
	char		*prefix;
};

# define ASMFILE_FLAG (O_CREAT | O_TRUNC | O_WRONLY)
# define ASMFILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH)

#endif
