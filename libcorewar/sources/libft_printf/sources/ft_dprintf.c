/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 09:59:17 by afeuerst          #+#    #+#             */
/*   Updated: 2019/11/17 10:05:17 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_printf_internal.h"

static int						ft_dprintf_function(const char *const formatted, const size_t length);

static struct s_printformat		printformat =
{
	.format = NULL,
	.args = 0,
	.percents = NULL,
	.length = 0,
	.ret = 0,
	.r1 = 0,
	.r2 = 0,
	.function = ft_dprintf_function
};

static int						ft_dprintf_function(const char *const formatted, const size_t length)
{
	return (int)write(printformat.r1, formatted, length);
}

int								ft_dprintf(const int fd, const char *const format, ...)
{
	printformat.length = 0;
	printformat.format = format;
	printformat.r1 = fd;
	va_start(printformat.args, format);
	ft_printf_core(&printformat, format, &printformat.percents);
	va_end(printformat.args);
	return (printformat.ret);
}
