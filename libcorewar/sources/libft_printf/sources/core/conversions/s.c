/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 08:40:35 by afeuerst          #+#    #+#             */
/*   Updated: 2019/11/14 09:57:45 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_printf_internal.h"

static const char		g_s_null[] = "(null)";

size_t					precalculate_s(struct s_printformat *const printformat, struct s_percent *const percent)
{
	const char *const	src = (const char*)percent->data;

	if (!src)
		return (sizeof(g_s_null));
	percent->r1 = 0;
	while (src[percent->r1])
		++percent->r1;
	return (percent->r1);
}

char					*transform_s(char *dst, struct s_percent *const percent)
{
	const char	*src;

	if (!percent->data)
		src = g_s_null;
	else
		src = (const char*)percent->data;
	while (*src)
		*dst++ = *src++;
	return (dst);
}
