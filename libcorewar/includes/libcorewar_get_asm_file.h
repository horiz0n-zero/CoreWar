/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libcorewar_get_asm_file.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 11:45:34 by afeuerst          #+#    #+#             */
/*   Updated: 2019/11/15 14:34:54 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBCOREWAR_GET_ASM_FILE_H
# define LIBCOREWAR_GET_ASM_FILE_H

# include "libcorewar.h"

static struct s_libcorewar_asm_file	*get_asm_file_opcodes(struct s_libcorewar_asm_file *const file, char **const error) __attribute__((always_inline));

#endif
