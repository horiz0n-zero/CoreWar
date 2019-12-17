/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 09:40:13 by afeuerst          #+#    #+#             */
/*   Updated: 2019/12/14 12:01:41 by afeuerst         ###   ########.fr       */
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

# define COF (O_CREAT | O_TRUNC | O_WRONLY)
# define COM (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH)

struct								s_champion_info
{
	const char						*named;
	uint32_t						id;
	uint32_t						flags;
	# define FLAGS_CHAMPION_N 1 << 0
	# define FLAGS_CHAMPION_C 1 << 1
	unsigned char					colorid;
};

struct								s_corewar
{
	int								flags;
	int								fd;
	char							*number_dump;
	char							*number_show;
	char							*file_output;
	uint32_t						dump;
	uint32_t						show;
	struct s_libcorewar_arena		*arena;
	char							*error;
	struct s_champion_info			info[MAX_PLAYERS];
	int								info_count;
} __attribute__((packed,aligned(8)));
extern struct s_corewar				g_corewar;

void								corewar_verbosity(void) __attribute__((always_inline));
void								corewar_setup(void) __attribute__((always_inline));
void								corewar_loop(void) __attribute__((always_inline));
void								corewar_dump(void);
void								corewar_dump_colors(void);
void								corewar_dump_binary(void);

void								arguments_parser(struct s_corewar *const corewar, char **argv);

void								handle_live(struct s_libcorewar_arena *const arena,
		struct s_libcorewar_process *const process);
void								handle_aff(struct s_libcorewar_arena *const arena,
		struct s_libcorewar_process *const process);
void								handle_info(struct s_libcorewar_arena *const arena,
		struct s_libcorewar_process *const process);

#endif
