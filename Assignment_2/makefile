#Variables
CC = gcc
CFLAGS = -Wall -pedantic -ansi -g
OBJ = maze.o map.o terminal.o dataconversion.o movement.o readfile.o snake.o linkedlist.o
EXEC = maze

#Conditional Compilation
ifdef DARK
CFLAGS += -D DARK
DARK: clean $(EXEC)
endif

#Compilation
$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) -lm

dataconversion.o: dataconversion.c
	$(CC) -c dataconversion.c $(CFLAGS)

map.o : map.c
	$(CC) -c map.c $(CFLAGS)

terminal.c : terminal.c
	$(CC) -c terminal.c $(CFLAGS)

movement.o : movement.c terminal.h
	$(CC) -c movement.c $(CFLAGS)

readfile.o : readfile.c
	$(CC) -c readfile.c $(CFLAGS)

snake.o: snake.c movement.h
	$(CC) -c snake.c $(CFLAGS) -lm

linkedlist.o : linkedlist.c
	$(CC) -c linkedlist.c $(CFLAGS)

maze.o : maze.c map.h dataconversion.h movement.h readfile.h snake.h linkedlist.h
	$(CC) -c maze.c $(CFLAGS)


#Cleaning up
clean:
	rm -f $(EXEC) $(OBJ)

