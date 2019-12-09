# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/15 09:22:08 by afeuerst          #+#    #+#              #
#    Updated: 2019/11/29 09:27:58 by afeuerst         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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
LIBFT_PRINTF_INC = ./libcorewar/sources/libft_printf/includes/

FLAGS = -O0 -g -Wno- -I $(LIBCOREWAR_INC) -I $(LIBFT_PRINTF_INC)

COREWAR = corewar
ASM = asm

all: Makefile $(LIBCOREWAR_LOCATION) $(ASM) $(COREWAR)

$(LIBCOREWAR_LOCATION): $(LIBCOREWAR_OBJECTS)
	ar -rcs $(LIBCOREWAR_LOCATION) $(LIBCOREWAR_OBJECTS)

%.o: %.c $(LIBCOREWAR_HEADERS) $(LIBFT_PRINTF)
	clang -c $(FLAGS) $< -o $@

$(ASM): $(LIBCOREWAR_LOCATION) $(ASM_SRC)
	clang -I $(ASM_INC) $(FLAGS) $(LIBCOREWAR_LOCATION) $(ASM_SRC) -o $(ASM)

$(COREWAR): $(LIBCOREWAR_LOCATION) $(COREWAR_SRC)
	clang -I $(COREWAR_INC) $(FLAGS) $(LIBCOREWAR_LOCATION) $(COREWAR_SRC) -o $(COREWAR)

clean:
	rm -rf $(LIBCOREWAR_OBJECTS)
	xcodebuild clean -project ./app/Corewar/Corewar.xcodeproj

fclean: clean
	rm -f $(LIBCOREWAR_LOCATION) $(ASM) $(COREWAR)
	rm -rf $(ASM).dSYM $(COREWAR).dSYM
	rm -rf Corewar.app

re: fclean all

bonus: $(LIBCOREWAR_LOCATION)
	xcodebuild -project ./app/Corewar/Corewar.xcodeproj
	cp -r app/Corewar/build/Release/Corewar.app .
