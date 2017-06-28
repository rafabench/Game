#ifndef FUNCOES_H
#define FUNCOES_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Defs.h"
#include "Globais.h"

void handleEvent(RECT *botao, SDL_Event* e, int w);

int menu();

int gameplay(SDL_Event e);

int playtypes(SDL_Event e);

int ranking(SDL_Event e);

int aboutus(SDL_Event e);

int init();

int loadMedia();

int ttfgame(char *vidas, char *pontos, char *niveis, char *speeds, char *time);

int check();

int gameover();

void handle_input(PLAT *p, SDL_Event event);

void closing();

SDL_Surface* loadSurface( char *path );

NPC createNPC( int posX, int posY, int stepX, int stepY, SDL_Surface *image);

BLOCO createBLOCO( int posX, int posY, SDL_Surface *image, int visible);

PLAT createPLATFORM( int posX, int posY, int stepX, int stepY, SDL_Surface *image);

IMAGEM createIMAGEM( int posX, int posY, SDL_Surface *image);

RECT createRECT( int posX, int posY);

void moveNPC(NPC *p, PLAT *ba);

void movePLATFORM( PLAT *p);

char* converteIntparaStr(int x);

char* converteDoubleparaStr(double x);

char* converteTimeparaStr(int *sec, int *min, int *hour);

#endif
