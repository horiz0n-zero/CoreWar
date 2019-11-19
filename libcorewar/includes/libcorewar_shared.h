/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libcorewar_shared.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 10:06:07 by afeuerst          #+#    #+#             */
/*   Updated: 2019/11/19 14:59:35 by afeuerst         ###   ########.fr       */
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

char			**arguments_get(char **argv, const struct s_argument *const arguments, int *const flags, char **const error);

size_t			ft_strlen(const char *const src);
int				ft_strcmp(const char *s1, const char *s2);
void			*ft_memalloc(const size_t size);
void			*ft_memcopy(const char *src, size_t length);
unsigned char	ft_hash_src(const char *src, size_t size);
char			*ft_static_world(char *content, char *const content_end, const int *const source, int *const length);
char			*ft_world(char *content, char *const content_end, const int *const source);

unsigned int	high_tone(unsigned int n);
int				multi_issafe(int lhs, int rhs);
int				add_issafe(int lhs, int rhs);
int				ft_src_unumber(const char *src, const int *const minmax, char **const error);
int				ft_src_number(const char *src, const int *const minmax, char **const error);
typedef int		(*t_src_number)(const char *src, const int *const minmax, char **const error);



#endif
