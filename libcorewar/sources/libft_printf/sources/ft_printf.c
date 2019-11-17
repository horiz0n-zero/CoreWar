/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 08:54:12 by afeuerst          #+#    #+#             */
/*   Updated: 2019/11/17 10:02:32 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_printf_internal.h"

static int									ft_printf_function(const char *const formatted, const size_t length)
{
	return (int)write(STDOUT_FILENO, formatted, length);
}

int											ft_printf(const char *const format, ...)
{
	static struct s_printformat				printformat = (struct s_printformat){
		.format = NULL,
		.args = 0,
		.percents = NULL,
		.length = 0,
		.ret = 0,
		.r1 = 0,
		.r2 = 0,
		.function = ft_printf_function
	};

	printformat.length = 0;
	printformat.format = format;
	va_start(printformat.args, format);
	ft_printf_core(&printformat, format, &printformat.percents);
	va_end(printformat.args);
	return (printformat.ret);
}





