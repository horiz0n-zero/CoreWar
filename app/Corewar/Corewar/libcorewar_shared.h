/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libcorewar_shared.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 10:06:07 by afeuerst          #+#    #+#             */
/*   Updated: 2019/11/18 15:37:37 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBCOREWAR_SHARED_H
# define LIBCOREWAR_SHARED_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <fcntl.h>
# include "libft_printf.h"

struct								s_argument
{
	const char						*name;
	const int						flags;
	const int						require;
	char **const					required;
};

char		**arguments_get(char **argv, const struct s_argument *const arguments, int *const flags, char **const error);

size_t		ft_strlen(const char *const src);
int			ft_strcmp(const char *s1, const char *s2);
void		*ft_memalloc(const size_t size);
void		*ft_memcopy(const char *src, size_t length);
char		*ft_static_world(char *content, char *const content_end, const int *const source, int *const length);
char		*ft_world(char *content, char *const content_end, const int *const source);


#endif
