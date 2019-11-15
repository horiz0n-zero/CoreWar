
include ../Makefile

all: $(LIBCOREWAR)

$(LIBCOREWAR): $(LIBCOREWAR_SRC)
	clang -c $(FLAGS) $(LIBCOREWAR_SRC)
	ar -rc $(LIBCOREWAR) $(LIBCOREWAR_OBJ)
