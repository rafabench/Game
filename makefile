CC=gcc

#CFLAGS=-g -Wall -D_GNU_SOURCE=1 -D_REENTRANT
CFLAGS=-g -Wall -D_GNU_SOURCE=1 -D_REENTRANT
SFLAGS=-lSDL2
IMAGE_FLAGS=-lSDL2_image
SOURCES=moveballkeyboard.c 
BINARIES=moveballkeyboard 


all: $(BINARIES)
	
moveballkeyboard: moveballkeyboard.c
	$(CC) -o moveballkeyboard moveballkeyboard.c $(CFLAGS) $(SFLAGS) $(IMAGE_FLAGS) 

clean:
	rm -rf *.o $(BINARIES) core a.out

