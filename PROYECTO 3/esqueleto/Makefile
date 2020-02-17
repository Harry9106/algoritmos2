CC=gcc
CFLAGS=-Wall -Werror -Wextra -pedantic -std=c99 -g
VAL=valgrind --leak-check=full --show-reachable=yes
OBJ= dict.o dict_helpers.o helpers.o map.o string.o
EXE= diccionario dict-test map-test

diccionario : $(OBJ) main.o
		$(CC) $(CFLAGS) -o diccionario $(OBJ) main.o
		$(VAL) ./diccionario

dict-test : $(OBJ) dict-test.o
		$(CC) $(CFLAGS) -o dict-test $(OBJ) dict-test.o
		$(VAL) ./dict-test

map-test : $(OBJ) map-test.o
		$(CC) $(CFLAGS) -o map-test $(OBJ) map-test.o
		$(VAL) ./map-test

.PHONY: clean

clean:
		rm -f $(EXE) *.o
