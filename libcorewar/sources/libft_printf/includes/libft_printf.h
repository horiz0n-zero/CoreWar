/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_printf.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 08:46:04 by afeuerst          #+#    #+#             */
/*   Updated: 2019/11/17 10:09:17 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_PRINTF_H
# define LIBFT_PRINTF_H

#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

int		ft_printf(const char *const format, ...);
int		ft_dprintf(const int fd, const char *const format, ...);
int		ft_asprintf(char **const ret, const char *const format, ...);

int		ft_vasprintf(char **const ret, const char *const format, va_list args);

#endif
