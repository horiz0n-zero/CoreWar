/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 09:06:15 by afeuerst          #+#    #+#             */
/*   Updated: 2019/11/23 13:36:38 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_printf_internal.h"

static const char	g_x_base[] = "0123456789abcdef";

size_t			precalculate_x(struct s_printformat *const printformat, struct s_percent *const percent)
{
	percent->r1 = ft_printf_unumber_length(percent->data, 16);
	if (percent->flags & FLAGS_HASHTAG)
		percent->r1 += 2;
	if (percent->width && percent->width > percent->r1)
	{
		percent->r2 = percent->width - percent->r1;
		return (percent->width);
	}
	else
		percent->r2 = 0;
	return (percent->r1);
}

char			*transform_x(char *dst, struct s_percent *const percent)
{
	if (percent->r2 && !(percent->flags & (FLAGS_MINUS | FLAGS_ZERO)))
		while (percent->r2--)
			*dst++ = ' ';
	if (percent->flags & FLAGS_HASHTAG)
	{
		*dst++ = '0';
		*dst++ = 'x';
	}
	if (percent->r2 && !(percent->flags & FLAGS_MINUS) && percent->flags & FLAGS_ZERO)
		while (percent->r2--)
			*dst++ = '0';
	if (percent->flags & FLAGS_HASHTAG)
		dst += (percent->r1 - 2);
	else
		dst += percent->r1;
	ft_printf_unumber_transform(percent->data, 16, g_x_base, dst);
	if (percent->r2 && percent->flags & FLAGS_MINUS)
		while (percent->r2--)
			*dst++ = ' ';
	return (dst);
}
