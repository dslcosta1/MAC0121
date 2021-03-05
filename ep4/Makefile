CCFLAGS = -Wall -ansi -pedantic -O2
CC = gcc

ep4 : main.c listasligadas.o listaPalavras.o
	$(CC) $(CCFLAGS) -o ep4 -g main.c listasligadas.o listaPalavras.o

listasligadas.o : listasligadas.c listasligadas.h listaPalavras.h
	$(CC) $(CCFLAGS) -c listasligadas.c 

listaPalavras.o : listaPalavras.c listaPalavras.h
	$(CC) $(CCFLAGS) -c listaPalavras.c

.PHONY : clean
clean :
	-rm -f *.o ep4