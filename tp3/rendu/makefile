SRC=tp3_ballejos.c
SRC+=mt.c
EXE=tp3_ballejos

CC=gcc
CFLAGS:=-Wall -Wextra -MMD -Og -g
LDFLAGS:=-lm

OBJ=$(addprefix build/,$(SRC:.c=.o))
DEP=$(addprefix build/,$(SRC:.c=.d))

all: $(OBJ) 
	$(CC) -o $(EXE) $^ $(LDFLAGS)

build/%.o: %.c
	@mkdir -p build
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf build core *.o
	rm -rf $(EXE)

-include $(DEP)
