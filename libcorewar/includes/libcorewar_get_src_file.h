/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libcorewar_get_src_file.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 11:45:34 by afeuerst          #+#    #+#             */
/*   Updated: 2019/11/18 14:26:16 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBCOREWAR_GET_SRC_FILE_H
# define LIBCOREWAR_GET_SRC_FILE_H

# include "libcorewar.h"

typedef char	*(*t_state_func)(struct s_libcorewar_src_file *const file, char *content, int *const state, char **const error);

# define STATE_HEADER 0
# define STATE_OPCODE 1


char			*libcorewar_state_comment(struct s_libcorewar_src_file *const file, char *content, int *const state, char **const error);
char			*libcorewar_state_whitespace(struct s_libcorewar_src_file *const file, char *content, int *const state, char **const error);
char			*libcorewar_state_unexpected(struct s_libcorewar_src_file *const file, char *content, int *const state, char **const error);
char			*libcorewar_state_head_point(struct s_libcorewar_src_file *const file, char *content, int *const state, char **const error);
struct			s_libcorewar_head_point
{
	char		*name;
	size_t		getted;
	size_t		file_offset;
	size_t		file_length;
};
# define GETTED_NAME 1 << 0
# define GETTED_COMM 1 << 1
# define GETTED_ALL (GETTED_NAME | GETTED_COMM)
char			*libcorewar_state_opcode(struct s_libcorewar_src_file *const file, char *content, int *const state, char **const error);


#endif
