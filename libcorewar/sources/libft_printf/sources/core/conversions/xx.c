/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xx.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 09:06:21 by afeuerst          #+#    #+#             */
/*   Updated: 2019/11/14 09:56:17 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_printf_internal.h"

static const char	g_xx_base[] = "0123456789ABCDEF";

size_t			precalculate_xx(struct s_printformat *const printformat, struct s_percent *const percent)
{
	return ((percent->r1 = ft_printf_unumber_length(percent->data, 16)));
}

char			*transform_xx(char *dst, struct s_percent *const percent)
{
	dst += percent->r1;
	ft_printf_unumber_transform(percent->data, 16, g_xx_base, dst);
	return (dst);
}
