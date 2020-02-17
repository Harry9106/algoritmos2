CC=gcc
CFLAGS=-Wall -Werror -Wextra -pedantic -std=c99 -g
VAL=valgrind --leak-check=full --show-reachable=yes
OBJ= helpers.o item.o knapsack.o string.o
EXE= knapsack

knapsack : $(OBJ) main.o
		$(CC) $(CFLAGS) -o knapsack $(OBJ) main.o
		$(VAL) ./knapsack

main-test : $(OBJ) main.o
		$(CC) $(CFLAGS) -o knapsack $(OBJ) main.o
		$(VAL) ./knapsack -bdst -f input/example0.in


.PHONY: clean

clean:
		rm -f $(EXE) *.o
