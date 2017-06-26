#ifndef DEFS_H
#define DEFS_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

typedef int bool;

typedef struct _NPC {
    int posX;
    int posY;
    int stepX;
    int stepY;
    SDL_Surface* image;
    int imgW;
    int imgH;
    int visible;
} NPC;

typedef struct _BLOCO {
    int posX;
    int posY;
    SDL_Surface* image;
    int imgW;
    int imgH;
    int visible;
} BLOCO;

typedef struct _PLAT {
    int posX;
    int posY;
    int stepX;
    int stepY;
    SDL_Surface* image;
    int imgW;
    int imgH;
} PLAT;

typedef struct _IMAGEM {
    int posX;
    int posY;
    SDL_Surface* image;
    int imgW;
    int imgH;
} IMAGEM;

typedef struct _RECT {
	int posX;
	int posY;
	int imgW;
	int imgH;
} RECT;

#endif
