/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 08:40:35 by afeuerst          #+#    #+#             */
/*   Updated: 2019/11/23 09:28:19 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_printf_internal.h"

static const char		g_s_null[] = "(null)";

size_t					precalculate_s(struct s_printformat *const printformat, struct s_percent *const percent)
{
	const char			*src;
	size_t				tmp;

	if (percent->data)
		src = (const char*)percent->data;
	else
		src = g_s_null;
	percent->r1 = 0;
	while (src[percent->r1])
		++percent->r1;
	if (percent->precision && percent->precision < percent->r1)
		percent->r1 = percent->precision;
	if (percent->width && percent->width > percent->r1)
	{
		percent->r2 = percent->width - percent->r1;
		return (percent->width);
	}
	else
		percent->r2 = 0;
	return (percent->r1);
}

char					*transform_s(char *dst, struct s_percent *const percent)
{
	const char			*src;

	if (!percent->data)
		src = g_s_null;
	else
		src = (const char*)percent->data;
	if (percent->r2 && !(percent->flags & FLAGS_MINUS))
		while (percent->r2--)
			*dst++ = ' ';
	while (percent->r1--)
		*dst++ = *src++;
	if (percent->r2 && percent->flags & FLAGS_MINUS)
		while (percent->r2--)
			*dst++ = ' ';
	return (dst);
}
