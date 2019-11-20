/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libcorewar.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 10:05:14 by afeuerst          #+#    #+#             */
/*   Updated: 2019/11/19 14:26:34 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBCOREWAR_H
# define LIBCOREWAR_H

# include "libcorewar_shared.h"

# define IND_SIZE 2
# define REG_SIZE 1
# define DIR_SIZE 4

# define REG_CODE 1
# define DIR_CODE 2
# define IND_CODE 3

# define T_REG 1
# define T_DIR 2
# define T_IND 4
# define T_LAB 8

# define COMMENT_CHAR '#'
# define LABEL_CHAR ':'
# define DIRECT_CHAR '%'
# define REG_CHAR 'r'
# define SEPARATOR_CHAR ','

# define LABEL_CHARS "abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING ".name"
# define PROG_NAME_LENGTH (128)
# define COMMENT_CMD_STRING ".comment"
# define COMMENT_LENGTH (2048)

# define REG_NUMBER 16

# define CYCLE_TO_DIE 1536
# define CYCLE_DELTA 50
# define NBR_LIVE 21
# define MAX_CHECKS 10
# define MAX_ARGS_NUMBER 4
# define MAX_PLAYERS 4
# define MEM_SIZE (4 * 1024)
# define IDX_MOD (MEM_SIZE / 8)
# define CHAMP_MAX_SIZE (MEM_SIZE / 6)

# define COREWAR_EXEC_MAGIC 0xea83f3

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
	const int								parameters_encoding;
	const int								parameters_direct_small;
	const int								opvalue;
	const int								pad;
	const int								parameters_type[MAX_ARGS_NUMBER];
};

/* ************************************************************************** */
/* *** MAIN STRUCT *** */

typedef struct s_libcorewar_opcode_get		t_libcorewar_opcode_get;
typedef struct s_libcorewar_asm_file		t_libcorewar_asm_file;
typedef struct s_libcorewar_opcode_src		t_libcorewar_opcode_src;

struct										s_libcorewar_opcode_get
{
	const t_libcorewar_ref_opcode_get		*ref;
	char									*start;
	char									*label;
	int										parameters[MAX_ARGS_NUMBER];
	int										parameters_type[MAX_ARGS_NUMBER];
	const void								*parameters_labels[MAX_ARGS_NUMBER];
	struct s_libcorewar_opcode_get			*next;
};

struct										s_libcorewar_asm_file // source is .cor
{
	struct stat								content_stat;
	char									*content;
	char									*content_end;
	const char								*labels_prefix;
	int										labels_count;
	int										pad;
	struct s_asm_header						*header;
	struct s_libcorewar_opcode_get			*opcodes;
};

struct										s_libcorewar_opcode_src
{
	char									*label;
	const t_libcorewar_ref_opcode_get		*ref;
	int										parameters[MAX_ARGS_NUMBER];
	int										parameters_type[MAX_ARGS_NUMBER];
	char									*parameters_labels[MAX_ARGS_NUMBER];
	struct s_libcorewar_opcode_src			*next;
};

struct										s_libcorewar_src_file
{
	struct stat								content_stat;
	char									*content;
	char									*content_end;
	struct s_asm_header						header;
	struct s_libcorewar_opcode_src			*opcodes;
};

/* ************************************************************************** */
struct s_libcorewar_asm_file	*libcorewar_get_asm_file(const char *const named, char **const error, const char *const prefix);
struct s_libcorewar_src_file	*libcorewar_get_src_file(const char *const named, char **const error);

// print out
void							libcorewar_out_asm_file(const int fd, struct s_libcorewar_asm_file *const file);
void							libcorewar_out_asm_file_hexcolors(const int fd, struct s_libcorewar_asm_file *const file);

// special
void							*libcorewar_error(char *const ptr, char **const error_ptr, ...);





#endif
