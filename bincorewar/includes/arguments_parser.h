/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments_parser.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 13:01:07 by afeuerst          #+#    #+#             */
/*   Updated: 2019/12/11 13:10:21 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGUMENTS_PARSER_H
# define ARGUMENTS_PARSER_H

# include "corewar.h"

static char	**argument_short(char **argv, int *const flags, int *const champi, char **const error) __attribute__((always_inline));
static char	**argument_long(char **argv, int *const flags, int *const champi, char **const error) __attribute__((always_inline));
static void	arguments_champions(struct s_corewar *const corewar, char **argv) __attribute__((always_inline));

typedef void						(*t_champion_arg)(struct s_corewar *const corewar, const char *arg);
void								champion_arg_id(struct s_corewar *const corewar, const char *arg);
void								champion_arg_color(struct s_corewar *const corewar, const char *arg);

struct								s_chargument
{
	const char						*named;
	t_champion_arg					func;
};


#endif
