/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 09:40:13 by afeuerst          #+#    #+#             */
/*   Updated: 2019/12/06 14:19:42 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "libcorewar.h"

# define FLAGS_D 1 << 0
# define FLAGS_S 1 << 1
# define FLAGS_O 1 << 2
# define FLAGS_B 1 << 3
# define FLAGS_C 1 << 4
# define FLAGS_A 1 << 5
# define FLAGS_L 1 << 6
# define FLAGS_V 1 << 7
# define FLAGS_P 1 << 8
# define FLAGS_Q 1 << 9

struct								s_champion_info
{
	const char						*named;
	uint32_t						id;
	int								pad;
};

struct								s_corewar
{
	int								flags;
	int								fd;
	const char						*number_dump;
	const char						*number_show;
	const char						*file_output;
	int								dump;
	int								show;
	struct s_libcorewar_arena		*arena;
	char							*error;
	struct s_champion_info			info[MAX_PLAYERS];
	int								info_count;
};
extern struct s_corewar				g_corewar;

static void							corewar_verbosity(void) __attribute__((always_inline));
static void							corewar_setup(void) __attribute__((always_inline));

void								arguments_parser(struct s_corewar *const corewar, char **argv);


void								handle_live(struct s_libcorewar_arena *const arena,
		struct s_libcorewar_process *const process, const int *const types, const int *const params);
void								handle_aff(struct s_libcorewar_arena *const arena,
		struct s_libcorewar_process *const process, const int *const types, const int *const params);
void								handle_info(struct s_libcorewar_arena *const arena,
		struct s_libcorewar_process *const process, const int *const types, const int *const params);

#endif
