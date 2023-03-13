# invoke linker only for linking
main: main.o snake.o
	gcc -o main main.o snake.o -lncurses
main.o: main.c snake.h
	gcc -c main.c 
snake.o: snake.c snake.h
	gcc -c snake.c
