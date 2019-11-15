
FLAGS = -O0 -g
INCLUDES = includes

LIBCOREWAR_DIR = libcorewar
COREWAR_DIR = corewar
ASM_DIR = asm
LIBCOREWAR_SRC = $(shell find $(LIBCOREWAR_DIR) -type f -name "*.c")
COREWAR_SRC = $(shell find $(COREWAR_DIR) -type f -name "*.c")
ASM_SRC = $(shell find $(ASM_DIR) -type f -name "*.c")
LIBCOREWAR_INC = $(join $(LIBCOREWAR_DIR), $(INCLUDES))
COREWAR_INC = $(join $(COREWAR_DIR), $(INCLUDES))
ASM_INC = $(join, $(ASM_DIR), $(INCLUDES))
LIBCOREWAR_HEADERS = $(shell find $(LIBCOREWAR_INC) -type f -name "*.h")
COREWAR_HEADERS = $(shell find $(LIBCOREWAR_INC) -type f -name "*.h")
ASM_HEADERS = $(shell find $(LIBCOREWAR_INC) -type f -name "*.h")

LIBCOREWAR = libcorewar.a
LIBCOREWAR_LOCATION = $(join $(LIBCOREWAR_DIR), $(LIBCOREWAR))
COREWAR = corewar
ASM = asm

all: $(LIBCOREWAR_LOCATION) $(ASM) $(COREWAR) Makefile

$(LIBCOREWAR_LOCATION): $(LIBCOREWAR_SRC) $(LIBCOREWAR_HEADERS)
	make -C $(LIBCOREWAR_DIR)

$(ASM): $(LIBCOREWAR) $(ASM_SRC)
	clang -I $(ASM_INC) $(FLAGS) $(LIBCOREWAR_LOCATION) $(ASM_SRC) -o $(ASM)

$(COREWAR): $(LIBCOREWAR) $(COREWAR_SRC)
	clang -I $(COREWAR_INC) $(FLAGS) $(LIBCOREWAR_LOCATION) $(COREWAR_SRC) -o $(COREWAR)

clean:
	echo clean;

fclean: clean
	echo fclean;

re: fclean all
