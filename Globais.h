#ifndef GLOBAIS_H
#define GLOBAIS_H
#define vb 1
#define lb 4
#define cb 10

#include "Defs.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern const int SCREEN_WIDTH_EXT;
extern const int SCREEN_HEIGHT_EXT;

typedef int bool;

extern Mix_Chunk* sound;
extern Mix_Chunk* sound1;
extern Mix_Chunk* sound2;
extern Mix_Music* CosmoMusic;
extern Mix_Chunk* nope;
/*Mix_Chunk* Bounce_Wall;
Mix_Chunk* Bounce_Block;
Mix_Music* Cosmo_Music;*/

extern const int false;
extern const int true;

extern const int IMAGE_WIDTH;
extern const int IMAGE_HEIGHT;

extern const int IMAGE_WIDTH_PLATFORM;
extern const int IMAGE_HEIGHT_PLATFORM;

extern const int IMAGE_WIDTH_BLOCO;
extern const int IMAGE_HEIGHT_BLOCO;

extern const int IMAGE_WIDTH_CORACAO;
extern const int IMAGE_HEIGHT_CORACAO;

extern const int IMAGE_WIDTH_BAR;
extern const int IMAGE_HEIGHT_BAR;

extern const int BUTTON_WIDTH;
extern const int BUTTON_HEIGHT;

extern int vida;
extern int ponto;
extern int contador;
extern int contador2;
extern int nivel;
extern int startclock;
extern int deltaclock;
extern int currentFPS;
extern int type;

/*
 * Global Variables
 */

/*The window we'll be rendering to*/
extern SDL_Window* gWindow;

extern SDL_Renderer* gRenderer ;

extern SDL_Surface* textSurface;
//Globally used font
extern TTF_Font *gFont;
extern TTF_Font *gFont1;
extern TTF_Font *gFont2;

//The actual hardware texture
extern SDL_Texture* font_texture;

//Image dimensions
extern int mWidth;
extern int mHeight;

/*The imagem character*/
extern NPC ball[vb];
extern PLAT platform;
extern BLOCO bloco[lb][cb];
extern IMAGEM coracao;
extern IMAGEM redbar;
extern IMAGEM greenbar;
extern RECT button[5];

/*The surface contained by the window*/
extern SDL_Surface* gScreenSurface;

extern int count;
/*Current displayed PNG image*/
extern SDL_Surface* gJPGSurface;
extern SDL_Surface* gJPGplatform;
extern SDL_Surface* gJPGbloco0;
extern SDL_Surface* gJPGbloco1;
extern SDL_Surface* gJPGbloco2;
extern SDL_Surface* gJPGbloco3;
extern SDL_Surface* gJPGbloco4;
extern SDL_Surface* gJPGbloco5;
extern SDL_Surface* gJPGcoracao;
extern SDL_Surface* gJPGredbar;
extern SDL_Surface* gJPGgreenbar;


#endif
