CREATER = gcc -Wall -ansi -pedantic
CLEAN 	= rm main.o tic_tac_toe.o
 
tic : main.o tic_tac_toe.o
	$(CREATER) -o tic_tac_toe tic_tac_toe.o main.o
	$(CLEAN)

tic_tac_toe.o : tic_tac_toe.c
	$(CREATER) -c tic_tac_toe.c

main.o : main.c tic_tac_toe.h
	$(CREATER) -c main.c

