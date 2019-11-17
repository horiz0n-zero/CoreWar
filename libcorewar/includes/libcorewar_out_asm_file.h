/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libcorewar_out_asm_file.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 13:37:52 by afeuerst          #+#    #+#             */
/*   Updated: 2019/11/17 14:04:49 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBCOREWAR_OUT_ASM_FILE_H
# define LIBCOREWAR_OUT_ASM_FILE_H

# include "libcorewar.h"

static void		out_asm_file_opcode(const int fd, struct s_libcorewar_opcode_get *const op) __attribute__((always_inline));
static void		out_asm_file_opcode_hexcolors(const int fd, struct s_libcorewar_opcode_get *const op) __attribute__((always_inline));

#endif
