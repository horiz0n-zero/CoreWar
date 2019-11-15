# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/15 09:22:08 by afeuerst          #+#    #+#              #
#    Updated: 2019/11/15 09:55:33 by afeuerst         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -O0 -g
COMPILER = $(shell xcrun --find clang)
INCLUDES = /includes

LIBCOREWAR_DIR = ./libcorewar
COREWAR_DIR = ./bincorewar
ASM_DIR = ./binasm
LIBCOREWAR_SRC = $(shell find $(LIBCOREWAR_DIR) -type f -name "*.c")
COREWAR_SRC = $(shell find $(COREWAR_DIR) -type f -name "*.c")
ASM_SRC = $(shell find $(ASM_DIR) -type f -name "*.c")
LIBCOREWAR_INC = $(join $(LIBCOREWAR_DIR), $(INCLUDES))
COREWAR_INC = $(join $(COREWAR_DIR), $(INCLUDES))
ASM_INC = $(join $(ASM_DIR), $(INCLUDES))
LIBCOREWAR_HEADERS = $(shell find $(LIBCOREWAR_INC) -type f -name "*.h")
COREWAR_HEADERS = $(shell find $(LIBCOREWAR_INC) -type f -name "*.h")
ASM_HEADERS = $(shell find $(LIBCOREWAR_INC) -type f -name "*.h")

LIBCOREWAR = libcorewar.a
LIBCOREWAR_LOCATION = $(join $(join $(LIBCOREWAR_DIR), /), $(LIBCOREWAR))
LIBCOREWAR_OBJECTS = $(LIBCOREWAR_SRC:.c=.o)
COREWAR = corewar
ASM = asm

all: $(LIBCOREWAR_LOCATION) $(ASM) $(COREWAR) Makefile

$(LIBCOREWAR_LOCATION): $(LIBCOREWAR_OBJECTS)
	ar -rcs $(LIBCOREWAR_LOCATION) $(LIBCOREWAR_OBJECTS)

%.o: %.c $(LIBCOREWAR_HEADERS)
	$(COMPILER) -c $(FLAGS) -I $(LIBCOREWAR_INC) $< -o $@

$(ASM): $(LIBCOREWAR_LOCATION) $(ASM_SRC)
	clang -I $(ASM_INC) $(FLAGS) $(LIBCOREWAR_LOCATION) $(ASM_SRC) -o $(ASM)

$(COREWAR): $(LIBCOREWAR_LOCATION) $(COREWAR_SRC)
	clang -I $(COREWAR_INC) $(FLAGS) $(LIBCOREWAR_LOCATION) $(COREWAR_SRC) -o $(COREWAR)

clean:
	rm -rf $(LIBCOREWAR_OBJECTS)

fclean: clean
	rm -f $(LIBCOREWAR_LOCATION) $(ASM) $(COREWAR)

re: fclean all
