SRC=tp4_simulation.c
SRC+=mt.c lapin.c
EXE=tp4_simulation

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
