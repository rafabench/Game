CC=gcc

CFLAGS=-g -Wall -D_GNU_SOURCE=1 -D_REENTRANT
#CFLAGS=-g -Wall -D_REENTRANT
IMAGE_FLAGS=-lSDL2_image
SFLAGS=-lSDL2
MIXER_FLAGS=-lSDL2_mixer
TEXT_FLAGS=-lSDL2_ttf
SOURCES=Breakout.c
BINARIES=Breakout

#all: ex0 ex1 ex2 ex3 ex4 ex5 ex6 ex7 grafico texto
all: $(BINARIES)

Breakout: Breakout.c
	$(CC) -o Breakout Breakout.c $(CFLAGS) $(SFLAGS) $(IMAGE_FLAGS) $(MIXER_FLAGS) $(TEXT_FLAGS)

clean:
	rm -rf *.o *.exe *.bak *.c~ $(BINARIES) core a.out
