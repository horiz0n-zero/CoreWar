/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libcorewar.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 10:05:14 by afeuerst          #+#    #+#             */
/*   Updated: 2019/11/15 15:29:27 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBCOREWAR_H
# define LIBCOREWAR_H

# include "libcorewar_shared.h"

# define IND_SIZE 2
# define REG_SIZE 4
# define DIR_SIZE REG_SIZE

# define REG_CODE 1
# define DIR_CODE 2
# define IND_CODE 3

# define MAX_ARGS_NUMBER 4
# define MAX_PLAYERS 4
# define MEM_SIZE (4 * 1024)
# define IDX_MOD (MEM_SIZE / 8)
# define CHAMP_MAX_SIZE (MEM_SIZE / 6)

# define COMMENT_CHAR '#'
# define LABEL_CHAR ':'
# define DIRECT_CHAR '%'
# define SEPARATOR_CHAR ','

# define LABEL_CHARS "abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING ".name"
# define COMMENT_CMD_STRING ".comment"

# define REG_NUMBER 16

# define CYCLE_TO_DIE 1536
# define CYCLE_DELTA 50
# define NBR_LIVE 21
# define MAX_CHECKS 10

typedef char	t_arg_type;

#define T_REG 1
#define T_DIR 2
#define T_IND 4
#define T_LAB 8

# define PROG_NAME_LENGTH (128)
# define COMMENT_LENGTH (2048)
# define COREWAR_EXEC_MAGIC 0xea83f3
# define COREWAR_EXEC_MAGIC_L 0xf383ea00

typedef struct								s_asm_header
{
	unsigned int							magic;
	char									prog_name[PROG_NAME_LENGTH + 1];
	unsigned int							prog_size;
	char									comment[COMMENT_LENGTH + 1];
}											t_asm_header;

/* ************************************************************************** */
/* *** OBJECTS STRUCT *** */

typedef struct s_libcorewar_ref_opcode_get	t_libcorewar_ref_opcode_get;

struct										s_libcorewar_ref_opcode_get
{
	const char								*name;
	const int								parameters;
	const int								instructions;
	const int								parameters_type[4];
};

/* ************************************************************************** */
/* *** MAIN STRUCT *** */

typedef struct s_libcorewar_opcode_get		t_libcorewar_opcode_get;
typedef struct s_libcorewar_asm_file		t_libcorewar_asm_file;

struct										s_libcorewar_opcode_get
{
	const t_libcorewar_ref_opcode_get		*ref;
	int										parameters[4];
	struct s_libcorewar_opcode_get			*next;
};

struct										s_libcorewar_asm_file // source is .cor
{
	struct stat								content_stat;
	char									*content;
	struct s_asm_header						*header;
	struct s_libcorewar_opcode_get			*opcodes;
};

/* ************************************************************************** */
struct s_libcorewar_asm_file	*libcorewar_get_asm_file(const char *const file, char **const error);




void							*libcorewar_error(char *const ptr, char **const error_ptr, ...);





#endif
