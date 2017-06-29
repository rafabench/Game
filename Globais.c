#include "Globais.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#define vb 1
#define lb 4
#define cb 10

const int SCREEN_WIDTH = 750;
const int SCREEN_HEIGHT = 520;

const int SCREEN_WIDTH_EXT = 930;
const int SCREEN_HEIGHT_EXT = 520;

typedef int bool;

Mix_Chunk* sound;
Mix_Chunk* sound1;
Mix_Chunk* sound2;
Mix_Chunk* nope;
Mix_Music* CosmoMusic;
/*Mix_Chunk* Bounce_Wall;
Mix_Chunk* Bounce_Block;
Mix_Music* Cosmo_Music;*/

const int false = 0;
const int true = 1;

const int IMAGE_WIDTH = 10;
const int IMAGE_HEIGHT = 10;

const int IMAGE_WIDTH_PLATFORM = 100;
const int IMAGE_HEIGHT_PLATFORM = 40;

const int IMAGE_WIDTH_BLOCO = 75;
const int IMAGE_HEIGHT_BLOCO = 50;

const int IMAGE_WIDTH_CORACAO = 49;
const int IMAGE_HEIGHT_CORACAO = 52;

const int IMAGE_WIDTH_BAR = 930;
const int IMAGE_HEIGHT_BAR = 40;

const int BUTTON_WIDTH = 490;
const int BUTTON_HEIGHT = 90;



int vida = 3;
int ponto = 0;
int contador = lb*cb;
int contador2 = 10000;
int nivel = 1; 
int startclock = 0;
int deltaclock = 0;
int currentFPS = 0;
int type = 0;

/*
 * Global Variables
 */

/*The window we'll be rendering to*/
SDL_Window* gWindow = NULL;

SDL_Renderer* gRenderer = NULL;

SDL_Surface* textSurface = NULL;
//Globally used font
TTF_Font *gFont = NULL;
TTF_Font *gFont1 = NULL;
TTF_Font *gFont2 = NULL;

//The actual hardware texture
SDL_Texture* font_texture = NULL;

//Image dimensions
int mWidth = 0;
int mHeight = 0;

/*The imagem character*/
NPC ball[vb];
PLAT platform;
BLOCO bloco[lb][cb];
IMAGEM coracao;
IMAGEM redbar;
IMAGEM greenbar;
RECT button[5];

/*The surface contained by the window*/
SDL_Surface* gScreenSurface = NULL;

int count;
/*Current displayed PNG image*/
SDL_Surface* gJPGSurface = NULL;
SDL_Surface* gJPGplatform = NULL;
SDL_Surface* gJPGbloco0 = NULL;
SDL_Surface* gJPGbloco1 = NULL;
SDL_Surface* gJPGbloco2 = NULL;
SDL_Surface* gJPGbloco3 = NULL;
SDL_Surface* gJPGbloco4 = NULL;
SDL_Surface* gJPGbloco5 = NULL;
SDL_Surface* gJPGcoracao = NULL;
SDL_Surface* gJPGredbar = NULL;
SDL_Surface* gJPGgreenbar = NULL;
