/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcopy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:35:17 by afeuerst          #+#    #+#             */
/*   Updated: 2019/11/18 15:59:06 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcorewar.h"

void			*ft_memcopy(const char *src, size_t len)
{
	char *const	ptr = malloc(len + 1);
	size_t		index;

	if (ptr)
	{
		index = 0;
		while (index < len)
		{
			*(ptr + index) = *(src + index);
			++index;
		}
		*(ptr + index) = 0;
	}
	return (ptr);
}
