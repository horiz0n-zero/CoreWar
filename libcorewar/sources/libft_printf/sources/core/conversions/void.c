/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   void.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 10:18:02 by afeuerst          #+#    #+#             */
/*   Updated: 2019/11/17 11:43:57 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_printf_internal.h"

static const char	nope[] = "(not found)";

size_t		precalculate_void(struct s_printformat *const printformat, struct s_percent *const percent)
{
	if (*(percent->format - 1) == '%')
		return (1);
	return (sizeof(nope));
}

char		*transform_void(char *dst, struct s_percent *const percent)
{
	const char	*t = nope;

	if (*(percent->format - 1) == '%')
	{
		*dst++ = '%';
		return (dst);
	}
	while (*t)
		*dst++ = *t++;
	return (dst);
}
