/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libcorewar_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 11:55:57 by afeuerst          #+#    #+#             */
/*   Updated: 2019/11/15 12:50:20 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcorewar.h"

void			*libcorewar_error(char *const ptr, char **const error_ptr, ...)
{
	va_list		args;
	void		*p;

	va_start(args, error_ptr);
	p = va_arg(args, void*);
	while (p)
	{
		free(p);
		p = va_arg(args, void*);
	}
	va_end(args);
	*error_ptr = ptr;
	return (NULL);
}
