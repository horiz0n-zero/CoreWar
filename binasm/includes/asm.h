/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 09:39:29 by afeuerst          #+#    #+#             */
/*   Updated: 2019/11/15 10:46:47 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "libcorewar.h"

# define FLAGS_O 1 << 0
# define FLAGS_D 1 << 1

struct			s_asm
{
	int			flags;
	int			toto;
	char		*out_directory;
};

#endif
