CC = gcc
OBJ = phsp
LDLIBS += -lm

all:
	$(CC) $(OBJ).c -o $(OBJ) -lm
