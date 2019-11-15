/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 10:41:37 by afeuerst          #+#    #+#             */
/*   Updated: 2019/11/15 10:44:20 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcorewar_shared.h"

size_t			ft_strlen(const char *const src)
{
	size_t		i;

	i = 0;
	while (src[i])
		++i;
	return (i);
}