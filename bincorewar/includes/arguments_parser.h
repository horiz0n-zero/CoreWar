/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments_parser.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 13:01:07 by afeuerst          #+#    #+#             */
/*   Updated: 2019/12/06 14:18:49 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGUMENTS_PARSER_H
# define ARGUMENTS_PARSER_H

# include "corewar.h"

static char	**argument_short(char **argv, int *const flags, int *const champi, char **const error) __attribute__((always_inline));
static char	**argument_long(char **argv, int *const flags, int *const champi, char **const error) __attribute__((always_inline));
static void	arguments_id_exist(struct s_corewar *const corewar, const int id) __attribute__((always_inline));
static void	arguments_champions(struct s_corewar *const corewar, char **argv) __attribute__((always_inline));

#endif
