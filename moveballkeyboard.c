#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

/*
 * Constants
 */

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int false = 0;
const int true = 1;

const int IMAGE_WIDTH = 61;
const int IMAGE_HEIGHT = 61;

typedef struct _NPC 
{
    int posX;
    int posY;
    int stepX;
    int stepY;
    SDL_Surface* image;
    int imgW;
    int imgH;
} NPC;

/*
 * Global Variables
 */

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The imagem character
NPC ball;
NPC ball2;
  
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//Current displayed PNG image
SDL_Surface* gJPGSurface = NULL;

/*
 * function prototypes
 */

//Starts up SDL and creates window
int init();
void update();
//Loads media
int loadMedia();

//Frees media and shuts down SDL
void closing();

//Loads individual image
SDL_Surface* loadSurface( char *path );

//Create NPC
NPC createNPC( int posX, int posY, int stepX, int stepY, SDL_Surface *image);

//Move NPC
void moveNPC(NPC *p);
void handle_input(NPC *p);

int main( int argc, char* args[] ) {
    SDL_Rect srcRect2, dstRect2;
    //Start up SDL and create window
    if( !init() ) {
        printf( "Failed to initialize!\n" );
    }
    else {
        //Load media
        if( !loadMedia() ) {
            printf( "Failed to load media!\n" );
        }
        else {   
            //Create NPC
            ball = createNPC(rand() % (SCREEN_WIDTH - IMAGE_WIDTH), 
                             rand() % (SCREEN_HEIGHT - IMAGE_HEIGHT), 
                             rand() % 2 ? -1: 1, 
                             rand() % 2 ? -1: 1, 
                             gJPGSurface);
                             
            ball2 = createNPC(rand() % (SCREEN_WIDTH - IMAGE_WIDTH), 
                             rand() % (SCREEN_HEIGHT - IMAGE_HEIGHT), 
                             0, 
                             0, 
                             gJPGSurface);
            //Main loop flag
            int quit = false;

            //Event handler
            SDL_Event e;

            //While application is running
            while( !quit ){
                while( SDL_PollEvent( &e ) != 0 ) {
                    switch (e.type) {
                        case SDL_QUIT:
                            quit = true;
                            break;
                        case SDL_KEYDOWN:
                            if (e.key.keysym.sym == SDLK_ESCAPE) {
                                quit = true;
                            }
                        break;
                    }
                }
            
                //Fill the surface white
                SDL_FillRect( gScreenSurface, NULL, 
                              SDL_MapRGB( gScreenSurface->format, 
                              0xFF, 0xFF, 0xFF ) );

                //moveNPC(&ball);
                moveNPC(&ball2);
                handle_input(&ball2);
                
                

                /*srcRect.x = 0; srcRect.y = 0;
                srcRect.w = IMAGE_WIDTH;
                srcRect.h = IMAGE_HEIGHT;
                dstRect.x = ball.posX;
                dstRect.y = ball.posY;
                if( SDL_BlitSurface( ball.image, &srcRect, 
                                     gScreenSurface, &dstRect ) < 0 ) {
                    printf( "SDL could not blit! SDL Error: %s\n", SDL_GetError() );
                    quit = true;
                }*/
                srcRect2.x = 0; srcRect2.y = 0;
                srcRect2.w = IMAGE_WIDTH;
                srcRect2.h = IMAGE_HEIGHT;
                dstRect2.x = ball2.posX;
                dstRect2.y = ball2.posY;
            
                if( SDL_BlitSurface( ball2.image, &srcRect2, 
                                     gScreenSurface, &dstRect2 ) < 0 ) {
                    printf( "SDL could not blit! SDL Error: %s\n", SDL_GetError() );
                    quit = true;
                }
                SDL_UpdateWindowSurface( gWindow );
                // Not so good solution, depends on your computer
                //SDL_Delay(7);
            }
        }
    }

    //Free resources and closing SDL
    closing();

    return 0;
}


void moveNPC(NPC *p) {
    p->posX += p->stepX;
    p->posY += p->stepY;
    if  (p->posX + IMAGE_WIDTH > SCREEN_WIDTH) {
        p->stepX = 0;
        p->posX = 0; 
    }
    if (p->posX < 0){
		p->stepX = 0;
		p->posX = SCREEN_HEIGHT + 1.5*IMAGE_WIDTH;
		
	} 
    if (p->posY + IMAGE_HEIGHT > SCREEN_HEIGHT) {
        p->stepY = 0;
        p->posY = 0;
    }
    if(p->posY < 0){
		p->posY = SCREEN_HEIGHT - IMAGE_HEIGHT;
		p->stepY = 0;
	}
    SDL_Delay(7);
}


//Create NPC
NPC createNPC( int posX, int posY, int stepX, int stepY, 
               SDL_Surface *image) {
    NPC p;
    
    p.posX = posX;
    p.posY = posY;
    p.stepX = stepX;
    p.stepY = stepY;
    p.image = image;
    return p;
}

int init() {
    //Initialization flag
    int success = true;

    srand(time(NULL));

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else {
        //Create window
        gWindow = SDL_CreateWindow( "SDL Tutorial: 06_moving_images", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL ) {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Initialize JPG and PNG loading 
            int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
            if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
                printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                success = false;
            }
            else {
                //Get window surface
                gScreenSurface = SDL_GetWindowSurface( gWindow );
            }
        }
    }

   

    return success;
}
void handle_input(NPC *p) {
	SDL_Event event;
	while(SDL_PollEvent( &event ) != 0){
		if( event.type == SDL_KEYDOWN ) {
			switch( event.key.keysym.sym ) { 
				case SDLK_UP: 
				p->posY -= IMAGE_HEIGHT / 4; 
				p->stepY -= IMAGE_HEIGHT / 16; 
				break; 
				case SDLK_DOWN: 
				p->posY += IMAGE_WIDTH / 4; 
				p->stepY += IMAGE_HEIGHT / 16; 
				break; 
				case SDLK_LEFT: 
				p->posX -= IMAGE_HEIGHT / 4; 
				p->stepX -= IMAGE_HEIGHT / 16; 
				break; 
				case SDLK_TAB: 
				p->posX += IMAGE_WIDTH; 
				gScreenSurface = SDL_GetWindowSurface( gWindow );
				break; 
				case SDLK_RIGHT: 
				p->posX += IMAGE_WIDTH/4; 
				p->stepX += IMAGE_HEIGHT / 16;
			} 
		}
		else if( event.type == SDL_KEYUP ) {
			switch( event.key.keysym.sym ) { 	
				case SDLK_UP: 
				p->posY -= IMAGE_HEIGHT / 4; 
				p->stepY = 0; 
				break; 
				case SDLK_DOWN: 
				p->posY += IMAGE_WIDTH / 4;
				p->stepY = 0;  
				break; 
				case SDLK_LEFT: 
				p->posX -= IMAGE_HEIGHT / 4; 
				p->stepX = 0; 
				break; 
				case SDLK_TAB: 
				p->posX += IMAGE_WIDTH; 
				gScreenSurface = SDL_GetWindowSurface( gWindow );
				break; 
				case SDLK_RIGHT: 
				p->posX += IMAGE_WIDTH/4; 
				p->stepX = 0;
				}  
			}
		}
}

int loadMedia() {
    //Loading success flag
    int success = true;
    //uint32_t colorKey;
    
    //Load PNG surface
    gJPGSurface = loadSurface( "./circle.jpeg" );
    if( gJPGSurface == NULL ) {
        printf( "Failed to load image! SDL Error: %s\n", SDL_GetError() );
        success = false;
    } 
    return success;
}

void closing() {
    //Free loaded image
    SDL_FreeSurface( gJPGSurface );
    gJPGSurface = NULL;

    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

SDL_Surface* loadSurface( char *path ) {
    //The final optimized image
    SDL_Surface* optimizedSurface = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path );
    if( loadedSurface == NULL ) {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError() );
    }
    else {
        //Convert surface to screen format
        optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, 0 );
        if( optimizedSurface == NULL ) {
            printf( "Unable to optimize image %s! SDL Error: %s\n", path, SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return optimizedSurface;
}



