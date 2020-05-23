all:	 program
program: program.o arg.o matrix.o
	gcc -o program  program.o arg.o matrix.o -lm

arg.o : arg.c
	gcc -c	arg.c

matrix.o : matrix.c
	gcc -c	matrix.c


program.o :program.c
	gcc -c	program.c

clear:
	rm *.o