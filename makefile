CC=gcc

CFLAGS=-g -Wall -D_GNU_SOURCE=1 -D_REENTRANT
#CFLAGS=-g -Wall -D_REENTRANT
MATH_FLAGS=-lm
IMAGE_FLAGS=-lSDL2_image
SFLAGS=-lSDL2
MIXER_FLAGS=-lSDL2_mixer
TEXT_FLAGS=-lSDL2_ttf
SOURCES=main.c funcoes.c Globais.c
OBJECTS=main.o funcoes.o Globais.o
BINARIES=main

#all: ex0 ex1 ex2 ex3 ex4 ex5 ex6 ex7 grafico texto
all: $(BINARIES)

main: main.o funcoes.o Globais.o
	$(CC) -o main main.o funcoes.o Globais.o $(SFLAGS) $(IMAGE_FLAGS) $(MIXER_FLAGS) $(TEXT_FLAGS)

main.o: main.c
	$(CC) -c main.c $(CFLAGS) $(MATH_FLAGS) $(SFLAGS) $(IMAGE_FLAGS) $(MIXER_FLAGS) $(TEXT_FLAGS)

funcoes.o: funcoes.c
	$(CC) -c funcoes.c $(CFLAGS) $(SFLAGS) $(IMAGE_FLAGS) $(MIXER_FLAGS) $(TEXT_FLAGS)
	
Globais.o: Globais.c
	$(CC) -c Globais.c $(CFLAGS) $(SFLAGS) $(IMAGE_FLAGS) $(MIXER_FLAGS) $(TEXT_FLAGS)
	
clean:
	rm -rf *.o *.exe *.bak *.c~ $(BINARIES) core a.out

limpa:
	del *.o *.exe *.bak *.c~ $(BINARIES) core
