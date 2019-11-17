/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 09:06:15 by afeuerst          #+#    #+#             */
/*   Updated: 2019/11/17 14:22:42 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_printf_internal.h"

static const char	g_x_base[] = "0123456789abcdef";

size_t			precalculate_x(struct s_printformat *const printformat, struct s_percent *const percent)
{
	if (percent->flags & FLAGS_HASHTAG)
		return (2 + (percent->r1 = ft_printf_unumber_length(percent->data, 16)));
	return ((percent->r1 = ft_printf_unumber_length(percent->data, 16)));
}

char			*transform_x(char *dst, struct s_percent *const percent)
{
	if (percent->flags & FLAGS_HASHTAG)
	{
		*dst++ = '0';
		*dst++ = 'x';
	}
	dst += percent->r1;
	ft_printf_unumber_transform(percent->data, 16, g_x_base, dst);
	return (dst);
}
