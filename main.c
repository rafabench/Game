#include "Defs.h"
#include "Globais.h"
#include "funcoes.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main( int argc, char* args[] ) {
    /*Start up SDL and create window*/
    if( !init() ) {
        printf( "Failed to initialize!\n" );
        
    }
    else {
        /*Load media*/
        if( !loadMedia() ) {
            printf( "Failed to load media!\n" );
        }
        else {
			menu();
        }
    }

    /*Free resources and closing SDL*/
    closing();

    return 0;
}
