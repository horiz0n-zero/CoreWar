/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 08:50:48 by afeuerst          #+#    #+#             */
/*   Updated: 2019/10/31 14:10:57 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_printf_internal.h"

static const char	g_u_base[] = "0123456789";

size_t				precalculate_u(struct s_printformat *const printformat, struct s_percent *const percent)
{
	return ((percent->r1 = ft_printf_unumber_length(percent->data, 10)));
}

char				*transform_u(char *dst, struct s_percent *const percent)
{
	dst += percent->r1;
	ft_printf_unumber_transform(percent->data, 10, g_u_base, dst);
	return (dst);
}
