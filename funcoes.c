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

/*Create NPC*/
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
BLOCO createBLOCO( int posX, int posY, 
					SDL_Surface *image, int visible) {
    BLOCO p;
    
    p.posX = posX;
    p.posY = posY;
    p.image = image;
    p.visible = visible;
    return p;
}
PLAT createPLATFORM( int posX, int posY, int stepX, int stepY, 
               SDL_Surface *image) {
    PLAT p;
    
    p.posX = posX;
    p.posY = posY;
    p.stepX = stepX;
    p.stepY = stepY;
    p.image = image;
    return p;
}

IMAGEM createIMAGEM( int posX, int posY, 
					SDL_Surface *image) {
    IMAGEM p;
    
    p.posX = posX;
    p.posY = posY;
    p.image = image;	
    return p;
}

RECT createRECT( int posX, int posY) {
    RECT p;
    
    p.posX = posX;
    p.posY = posY;	
    return p;
}


char* converteIntparaStr(int x){
	char *str;
	str = (char *) malloc (200*sizeof(char));
	sprintf(str, "%d", x);
	return str;
}

char* converteDoubleparaStr(double x){
	char *str;
	str = (char *) malloc (200*sizeof(char));
	sprintf(str, "%1.3lf", x);
	return str;
}

char* converteTimeparaStr(int *sec, int *min, int *hour){
	char *str;
	str = (char *) malloc (1000*sizeof(char));
	sprintf(str, "%02d:%02d:%02d", *hour,*min,*sec);
	return str;
}

int gameover(){
	
	/*FILL SURFACE BLACK*/
	
	SDL_FillRect( gScreenSurface, NULL, 
                              SDL_MapRGB( gScreenSurface->format, 
                              0x00, 0x00, 0x00 ) );
	SDL_Color backgroundColor = { 0, 0, 0 };
	SDL_Color foregroundColor = { 255, 255, 255 };
	
	/*BLIT GAME OVER*/
	
	SDL_Surface* textSurface = TTF_RenderText_Shaded(gFont1, "GAME OVER", foregroundColor, backgroundColor);
	SDL_Rect textLocation = { 50, 150, 200, 200 };              
    SDL_BlitSurface(textSurface, NULL, gScreenSurface, &textLocation);
    
    SDL_UpdateWindowSurface( gWindow );
    SDL_Delay(3000);
    exit(1);
    
	return 1;
}

int check(){
	int i,j;
	if(contador2 <= 0 && vida <= 9){
		contador2 = 10000;
		vida += 1;
	}
	else if(contador2 <= 0 && vida >= 10){
		contador2 = 10000;
	}
	if(!contador){
		contador = cb*lb;
		nivel += 1;
		ponto += 1000;
		contador2 -= 1000;
		ball[0].posX = platform.posX + IMAGE_WIDTH_PLATFORM/2;
		ball[0].posY = platform.posY - IMAGE_HEIGHT_PLATFORM/2;
		for(i = 0 ; i < lb ; i++){
			for(j = 0 ; j < cb ; j++){
				bloco[i][j].visible = 1;
			}
		}
	}
	if(!vida){
		gameover();
	}
	return 1;
}

void moveNPC(NPC *p, PLAT *ba) {
	int i, j;
    p->posX += p->stepX;
    p->posY += p->stepY;
    
    if ( (p->posX + IMAGE_WIDTH >= SCREEN_WIDTH) ||
         (p->posX < 0) ) {
          p->stepX = -p->stepX;
          p->posX += p->stepX;
	      Mix_PlayChannel(-1,sound2, 0);
    }
    if (p->posY <= 0) {
        p->stepY = -p->stepY;
        p->posY += p->stepY;
        Mix_PlayChannel(-1,sound2, 0);
    }
    if (p->posY + IMAGE_HEIGHT >= SCREEN_HEIGHT)	{
		p->stepY = -p->stepY;
        p->posY += p->stepY;
        Mix_PlayChannel(-1,nope, 0);
        vida -= 1;
        SDL_Delay(1000);
        p->posX = ba->posX + IMAGE_WIDTH_PLATFORM/2;
		p->posY = ba->posY - IMAGE_HEIGHT_PLATFORM/2; 
    }
    if (p->posY + IMAGE_HEIGHT == ba->posY &&
        p->posX + (IMAGE_WIDTH/2) <= ba->posX + IMAGE_WIDTH_PLATFORM &&
        p->posX + (IMAGE_WIDTH/2) >= ba->posX) {
		p->stepY = -(p->stepY);
		Mix_PlayChannel(-1, sound2, 0);
	}
	for(i = 0 ; i < lb ; i++){
		for(j = 0 ; j < cb ; j++){
			if(!bloco[i][j].visible){
				continue;
			}
			if(p->posX + (IMAGE_WIDTH/2) <= bloco[i][j].posX + IMAGE_WIDTH_BLOCO &&
				p->posX + (IMAGE_WIDTH/2) >= bloco[i][j].posX){
				if(p->posY + IMAGE_HEIGHT == bloco[i][j].posY || p->posY == bloco[i][j].posY + IMAGE_HEIGHT_BLOCO){
					p->stepY = -(p->stepY);
					bloco[i][j].visible = 0;
					ponto += 100;
					contador--;
					contador2 -= 100;
					Mix_PlayChannel(-1,sound1, 0);
				}
			}
			if(p->posY + (IMAGE_HEIGHT/2) <= bloco[i][j].posY + IMAGE_HEIGHT_BLOCO &&
				p->posY + (IMAGE_HEIGHT/2) >= bloco[i][j].posY){
				if(p->posX + IMAGE_WIDTH == bloco[i][j].posX || p->posX == bloco[i][j].posX + IMAGE_WIDTH_BLOCO){
					p->stepX = -(p->stepX);
					bloco[i][j].visible = 0;
					ponto += 100;
					contador--;
					contador2 -= 100;
					Mix_PlayChannel(-1,sound1, 0);
			}
			}
		}
	}
}

void handle_input(PLAT *p, SDL_Event event) {
	/*SDL_Event event;*/
	/*while(SDL_PollEvent( &event ) != 0){*/
	if( event.type == SDL_KEYDOWN ) {
		switch( event.key.keysym.sym ) {  
			case SDLK_LEFT: 
			/*p->posX -= IMAGE_HEIGHT / 4;*/
			p->stepX = -4; 
			break; 
			case SDLK_TAB: 
			/*p->posX += IMAGE_WIDTH; */
			gScreenSurface = SDL_GetWindowSurface( gWindow );
			break; 
			case SDLK_RIGHT: 
			/*p->posX += IMAGE_WIDTH/4;*/
			p->stepX = 4;
		} 
	}
	else if( event.type == SDL_KEYUP ) {
		switch( event.key.keysym.sym ) {
			case SDLK_LEFT: 
			/*p->posX -= IMAGE_HEIGHT / 4;*/
			p->stepX = 0; 
			break; 
			case SDLK_TAB: 
			/*p->posX += IMAGE_WIDTH; */
			gScreenSurface = SDL_GetWindowSurface( gWindow );
			break; 
			case SDLK_RIGHT: 
			/*p->posX += IMAGE_WIDTH/4;*/
			p->stepX = 0;
		}  
	}
		
}

void movePLATFORM( PLAT *p){

    
    if(p->posX + IMAGE_WIDTH_PLATFORM + p->stepX >= SCREEN_WIDTH) {
		p->stepX = 0;
		/*p->posX = SCREEN_HEIGHT + 1.7*IMAGE_WIDTH_PLATFORM;*/
	}
	if(p->posX + p->stepX<= 0) {
		p->stepX = 0;
		/*p->posX = 0;*/
	}
	
	p->posX += p->stepX;
	
}

int ttfgame(char *vidas, char *pontos, char *niveis, char *speeds, char *time){
	SDL_Color backgroundColor = { 0, 0, 0 };
	SDL_Color foregroundColor = { 255, 255, 255 };
	
	/*BLIT TIME*/
    
    SDL_Surface* textSurface9 = TTF_RenderText_Shaded(gFont, "TIME:" , foregroundColor, backgroundColor);
	SDL_Rect textLocation9 = { SCREEN_WIDTH + 10, 10, 400, 400 };              
    SDL_BlitSurface(textSurface9, NULL, gScreenSurface, &textLocation9);
    
    /*BLIT SEC,MIN,HOUR */

    SDL_Surface* textSurface10 = TTF_RenderText_Shaded(gFont, time, foregroundColor, backgroundColor);
	SDL_Rect textLocation10 = { SCREEN_WIDTH + 10, 55, 400, 400 };              
    SDL_BlitSurface(textSurface10, NULL, gScreenSurface, &textLocation10);
	
	/*BLIT VIDAS*/
	
	SDL_Surface* textSurface = TTF_RenderText_Shaded(gFont, "VIDAS:", foregroundColor, backgroundColor);
	SDL_Rect textLocation = { SCREEN_WIDTH + 10, 110, 400, 400 };              
    SDL_BlitSurface(textSurface, NULL, gScreenSurface, &textLocation);
    
    /*BLIT X*/
    
    SDL_Surface* textSurface1 = TTF_RenderText_Shaded(gFont, "x", foregroundColor, backgroundColor);
	SDL_Rect textLocation1 = { SCREEN_WIDTH + 65, 155, 400, 400 };              
    SDL_BlitSurface(textSurface1, NULL, gScreenSurface, &textLocation1);
    
    /*BLIT NUMERO DE VIDAS*/
    
    SDL_Surface* textSurface2 = TTF_RenderText_Shaded(gFont, vidas , foregroundColor, backgroundColor);
	SDL_Rect textLocation2 = { SCREEN_WIDTH + 95, 155, 400, 400 };              
    SDL_BlitSurface(textSurface2, NULL, gScreenSurface, &textLocation2);
    
    /*BLIT PONTOS*/
    
    SDL_Surface* textSurface3 = TTF_RenderText_Shaded(gFont, "PONTOS:" , foregroundColor, backgroundColor);
	SDL_Rect textLocation3 = { SCREEN_WIDTH + 10, 210, 400, 400 };              
    SDL_BlitSurface(textSurface3, NULL, gScreenSurface, &textLocation3);
    
    /*BLIT NUMERO DE PONTOS*/
    
    SDL_Surface* textSurface4 = TTF_RenderText_Shaded(gFont, pontos , foregroundColor, backgroundColor);
	SDL_Rect textLocation4 = { SCREEN_WIDTH + 10, 255, 400, 400 };              
    SDL_BlitSurface(textSurface4, NULL, gScreenSurface, &textLocation4);
    
    /*BLIT NIVEIS*/
    
    SDL_Surface* textSurface5 = TTF_RenderText_Shaded(gFont, "NIVEL:" , foregroundColor, backgroundColor);
	SDL_Rect textLocation5 = { SCREEN_WIDTH + 10, 310, 400, 400 };              
    SDL_BlitSurface(textSurface5, NULL, gScreenSurface, &textLocation5);
    
    /*BLIT NUMERO DO NIVEL*/
    
    SDL_Surface* textSurface6 = TTF_RenderText_Shaded(gFont, niveis, foregroundColor, backgroundColor);
	SDL_Rect textLocation6 = { SCREEN_WIDTH + 10, 355, 400, 400 };              
    SDL_BlitSurface(textSurface6, NULL, gScreenSurface, &textLocation6);
    
    /*BLIT SPEED*/
    
    SDL_Surface* textSurface7 = TTF_RenderText_Shaded(gFont, "FPS:" , foregroundColor, backgroundColor);
	SDL_Rect textLocation7 = { SCREEN_WIDTH + 10, 410, 400, 400 };              
    SDL_BlitSurface(textSurface7, NULL, gScreenSurface, &textLocation7);
    
    /*BLIT NUMERO DO SPEED*/

    SDL_Surface* textSurface8 = TTF_RenderText_Shaded(gFont, speeds, foregroundColor, backgroundColor);
	SDL_Rect textLocation8 = { SCREEN_WIDTH + 10, 455, 400, 400 };              
    SDL_BlitSurface(textSurface8, NULL, gScreenSurface, &textLocation8);
    
    
    
    return 1;
}

int gameplay(){
	SDL_Rect srcRect, dstRect;
    int i, j, rand0,rand1,rand2,rand3,rand4,rand5, secstart,seccurrent,timerun;
    int sec, min, hour;
    int *sec1, *min1, *hour1;
    int quit;
    rand0 = rand1 = rand2 = rand3 = rand4 = rand5 = 0;
    SDL_Event e;
	
	secstart = time(NULL);
	
	/*Create Platform*/

	platform = createPLATFORM((SCREEN_WIDTH - IMAGE_WIDTH_PLATFORM)/2, SCREEN_HEIGHT - (IMAGE_HEIGHT_PLATFORM + 10), 0, 0, gJPGplatform);
	
	/*Create NPC*/

	for(i = 0 ; i < vb ; i++){
            ball[i] = createNPC(platform.posX + IMAGE_WIDTH_PLATFORM/2,
							 platform.posY - IMAGE_HEIGHT_PLATFORM/2,
                             1, 
                             1, 
                             gJPGSurface);
	}
	rand0 = rand()%6;
	rand1 = (rand0+1)%6;
	rand2 = (rand1+1)%6;
	rand3 = (rand2+1)%6;
	rand4 = (rand3+1)%6;
	rand5 = (rand4+1)%6;
	/*Create Bloco*/
	for(i = 0 ; i < lb ; i++) {			
		for(j = 0 ; j < cb ; j++){
			if(i%6 == rand0) bloco[i][j] = createBLOCO(0+(j)*IMAGE_WIDTH_BLOCO, 0+(i)*IMAGE_HEIGHT_BLOCO,gJPGbloco0, 1);
			if(i%6 == rand1) bloco[i][j] = createBLOCO(0+(j)*IMAGE_WIDTH_BLOCO, 0+(i)*IMAGE_HEIGHT_BLOCO,gJPGbloco1, 1);
			if(i%6 == rand2) bloco[i][j] = createBLOCO(0+(j)*IMAGE_WIDTH_BLOCO, 0+(i)*IMAGE_HEIGHT_BLOCO,gJPGbloco2, 1);
			if(i%6 == rand3) bloco[i][j] = createBLOCO(0+(j)*IMAGE_WIDTH_BLOCO, 0+(i)*IMAGE_HEIGHT_BLOCO,gJPGbloco3, 1);
			if(i%6 == rand4) bloco[i][j] = createBLOCO(0+(j)*IMAGE_WIDTH_BLOCO, 0+(i)*IMAGE_HEIGHT_BLOCO,gJPGbloco4, 1);
			if(i%6 == rand5) bloco[i][j] = createBLOCO(0+(j)*IMAGE_WIDTH_BLOCO, 0+(i)*IMAGE_HEIGHT_BLOCO,gJPGbloco5, 1);
			}
		}
	
	/*Create Coracao*/
	
	coracao = createIMAGEM(SCREEN_WIDTH + 10, 150, gJPGcoracao);
	
	/*Main loop flag*/
	quit = false;

	/*While application is running*/
	while( !quit ) {
		startclock = SDL_GetTicks();
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
		
		check();
		
		deltaclock = SDL_GetTicks() - startclock;
		startclock = SDL_GetTicks();
		
		seccurrent = time(NULL);
		timerun = seccurrent - secstart;
		
		if ( deltaclock != 0 ) currentFPS = 1000 / deltaclock;
		
		sec = timerun % 60;
		timerun = timerun - sec;
		min = timerun % 3600;
		min = min/60;
		hour = (timerun - min)/3600;
		sec1 = &sec;
		min1 = &min;
		hour1 = &hour; 
	
		/*Fill the surface white*/
		SDL_FillRect( gScreenSurface, NULL, 
					  SDL_MapRGB( gScreenSurface->format, 
					  0x00, 0x00, 0x00 ) );
					  
		char *vidas;
		char *pontos;
		char *niveis;
		char *speeds;
		char *time;
		vidas = malloc(200*sizeof(char));
		pontos = malloc(200*sizeof(char));
		niveis = malloc(200*sizeof(char));
		speeds = malloc(200*sizeof(char));
		time = malloc(1000*sizeof(char));
		vidas = converteIntparaStr(vida);
		pontos = converteIntparaStr(ponto);
		niveis = converteIntparaStr(nivel);
		speeds = converteIntparaStr(currentFPS);
		time = converteTimeparaStr(sec1, min1, hour1);
		
		/*Using  TTF*/
		
		ttfgame(vidas, pontos, niveis, speeds, time);
		
		
		for(i = 0 ; i < vb ; i++){
			moveNPC(&ball[i], &platform);
			

			srcRect.x = 0; srcRect.y = 0;
			srcRect.w = IMAGE_WIDTH;
			srcRect.h = IMAGE_HEIGHT;
			dstRect.x = ball[i].posX;
			dstRect.y = ball[i].posY;
	
		
			if( SDL_BlitSurface( ball[i].image, &srcRect, 
								 gScreenSurface, &dstRect ) < 0 ) {
				printf( "SDL could not blit! SDL Error: %s\n", SDL_GetError() );
				quit = true;
			}
			
		}
		
		handle_input(&platform, e);
		movePLATFORM(&platform);
        /*handle_input(&platform);*/
        
        srcRect.x = 0; srcRect.y = 0;
		srcRect.w = IMAGE_WIDTH_PLATFORM;
		srcRect.h = IMAGE_HEIGHT_PLATFORM;
		dstRect.x = platform.posX;
		dstRect.y = platform.posY;

	
        if( SDL_BlitSurface( platform.image, &srcRect, 
                             gScreenSurface, &dstRect ) < 0 ) {
            printf( "SDL could not blit! SDL Error: %s\n", SDL_GetError() );
            quit = true;
        }
        
        
		for(j = 0 ; j < cb ; j++){
			for(i = 0 ; i < lb ; i++){
				if(bloco[i][j].visible == 1) {
					srcRect.x = 0; srcRect.y = 0;
					srcRect.w = IMAGE_WIDTH_BLOCO;
					srcRect.h = IMAGE_HEIGHT_BLOCO;
					dstRect.x = bloco[i][j].posX;
					dstRect.y = bloco[i][j].posY;
		
					if( SDL_BlitSurface( bloco[i][j].image, &srcRect, 
										gScreenSurface, &dstRect ) < 0 ) {
						printf( "SDL could not blit! SDL Error: %s\n", SDL_GetError() );
						quit = true;
					}
					
				}
			}
        }
        
        
        srcRect.x = 0; srcRect.y = 0;
		srcRect.w = IMAGE_WIDTH_CORACAO;
		srcRect.h = IMAGE_HEIGHT_CORACAO;
		dstRect.x = coracao.posX;
		dstRect.y = coracao.posY;
        if( SDL_BlitSurface( coracao.image, &srcRect, 
										gScreenSurface, &dstRect ) < 0 ) {
						printf( "SDL could not blit! SDL Error: %s\n", SDL_GetError() );
						quit = true;
					}
		/*Update the surface*/
		SDL_UpdateWindowSurface( gWindow );
		
		SDL_Delay(4);
	}
	return 1;
}

int ranking(){
	SDL_FillRect( gScreenSurface, NULL, 
					  SDL_MapRGB( gScreenSurface->format, 
					  0x00, 0x00, 0x00 ) );
	return 1;
}

int aboutus(){
	SDL_FillRect( gScreenSurface, NULL, 
					  SDL_MapRGB( gScreenSurface->format, 
					  0x00, 0x00, 0x00 ) );
					  
	SDL_Color backgroundColor = { 0, 0, 0 };
	SDL_Color foregroundColor = { 255, 255, 255 };
	SDL_Surface* textSurface = TTF_RenderText_Shaded(gFont, "EQUIPE:" , foregroundColor, backgroundColor);
	SDL_Rect textLocation = { SCREEN_WIDTH + 10, 410, 400, 400 };              
    SDL_BlitSurface(textSurface, NULL, gScreenSurface, &textLocation);
	return 1;
}



int menu(){
	SDL_Rect srcRect, dstRect;
	SDL_Event e;
	int quit = false,i;
	/*FILL SURFACE BLACK*/
	
	SDL_FillRect( gScreenSurface, NULL, 
                              SDL_MapRGB( gScreenSurface->format, 
                              0x00, 0x00, 0x00 ) );
	SDL_Color backgroundColor = { 0, 0, 0 };
	SDL_Color foregroundColor = { 255, 255, 255 };
	
	for(i = 0; i < 3; i++){
		button[i] = createRECT(215,220+(100*i));
	}
	
	while( !quit ) {
		startclock = SDL_GetTicks();
		startclock = SDL_GetTicks();
		while( SDL_PollEvent( &e ) != 0 ) {
			switch (e.type) {
				case SDL_QUIT:
					//quit = true;
					exit(1);
					break;
				case SDL_KEYDOWN:
					if (e.key.keysym.sym == SDLK_ESCAPE) {
						//quit = true;
						exit(1);
					}
				break;
			}
			for(w = 0; w < 3; w++){
				handleEvent(&button[w],&e);
			}
		}
		SDL_FillRect( gScreenSurface, NULL, 
                              SDL_MapRGB( gScreenSurface->format, 
                              0x00, 0x00, 0x00 ) );
	
		redbar = createIMAGEM(0, 0, gJPGredbar);
		greenbar = createIMAGEM(0, SCREEN_HEIGHT_EXT-IMAGE_HEIGHT_BAR, gJPGgreenbar);
		
		srcRect.x = 0; srcRect.y = 0;
		srcRect.w = IMAGE_WIDTH_BAR;
		srcRect.h = IMAGE_HEIGHT_BAR;
		dstRect.x = redbar.posX;
		dstRect.y = redbar.posY;
		if( SDL_BlitSurface( redbar.image, &srcRect, 
										gScreenSurface, &dstRect ) < 0 ) {
						printf( "SDL could not blit! SDL Error: %s\n", SDL_GetError() );
					}
					
		srcRect.x = 0; srcRect.y = 0;
		srcRect.w = IMAGE_WIDTH_BAR;
		srcRect.h = IMAGE_HEIGHT_BAR;
		dstRect.x = greenbar.posX;
		dstRect.y = greenbar.posY;
		if( SDL_BlitSurface( greenbar.image, &srcRect, 
										gScreenSurface, &dstRect ) < 0 ) {
						printf( "SDL could not blit! SDL Error: %s\n", SDL_GetError() );
					}
					
		/*BLIT TTFs*/			
		SDL_Surface* textSurface = TTF_RenderText_Shaded(gFont1, "BREAKOUT", foregroundColor, backgroundColor);
		SDL_Rect textLocation = { 90, 40, 200, 200 };              
		SDL_BlitSurface(textSurface, NULL, gScreenSurface, &textLocation);
		
		SDL_Surface* textSurface1 = TTF_RenderText_Shaded(gFont2, "PLAY", foregroundColor, backgroundColor);
		SDL_Rect textLocation1 = { 330, 190, 200, 200 };              
		SDL_BlitSurface(textSurface1, NULL, gScreenSurface, &textLocation1);
		
		SDL_Surface* textSurface2 = TTF_RenderText_Shaded(gFont2, "RANKING", foregroundColor, backgroundColor);
		SDL_Rect textLocation2 = { 250, 290, 200, 200 };              
		SDL_BlitSurface(textSurface2, NULL, gScreenSurface, &textLocation2);
		
		SDL_Surface* textSurface3 = TTF_RenderText_Solid(gFont2, "ABOUT US", foregroundColor);
		SDL_Rect textLocation3 = { 230, 390, 200, 200 };              
		SDL_BlitSurface(textSurface3, NULL, gScreenSurface, &textLocation3);
		
		SDL_UpdateWindowSurface( gWindow );
		//SDL_Delay(5000);
		//quit = true;
	}
	
    return 1;
}

void handleEvent(RECT *botao, SDL_Event* e ) {
    //If mouse event happened
    if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP ) {
        //Get mouse position
        int x, y;
        SDL_GetMouseState( &x, &y );

        //Check if mouse is in button
        bool inside = true;

        //Mouse is left of the button
        if( x < botao->posX ) {
            inside = false;
        }
        //Mouse is right of the button
        else if( x > botao->posX + BUTTON_WIDTH ) {
            inside = false;
        }
        //Mouse above the button
        else if( y < botao->posY ) {
            inside = false;
        }
        //Mouse below the button
        else if( y > botao->posY + BUTTON_HEIGHT ) {
            inside = false;
        }

        if( inside ) {
            //Set mouse over sprite
            switch( e->type ) {
                case SDL_MOUSEBUTTONDOWN:
					switch(w){
						case(0):
							gameplay();
							break;
						case(1):
							ranking();
							break;
						case(2):
							aboutus();
							break;
					}
                break;
                
                case SDL_MOUSEBUTTONUP:
					switch(w){
						case(0):
							gameplay();
							break;
						case(1):
							ranking();
							break;
						case(2):
							aboutus();
							break;
					}
                break;
            }
        }
    }
}


int init() {
    /*Initialization flag*/
    int success = true;

    srand(time(NULL));

    /*Initialize SDL*/
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
        return success;
    }
    if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ) {
		printf( "Warning: Linear texture filtering not enabled!" );
	}
    /*Create window*/
    gWindow = SDL_CreateWindow( "Breakout", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH_EXT, SCREEN_HEIGHT_EXT, SDL_WINDOW_SHOWN );
    if( gWindow == NULL ) {
		printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
		success = false;
        return success;
    }
    /*Initialize JPG and PNG loading */
    int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        success = false;
        return success;
	}
	gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
	if( gRenderer == NULL ){
		printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
		success = false;
		return success;
	}
	if( TTF_Init() == -1 )
	{
		printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                return false;
	}
	/*Get window surface*/
	gScreenSurface = SDL_GetWindowSurface( gWindow );
	
	
	//Initialize renderer color
	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
	Mix_AllocateChannels(16);
	
	sound = Mix_LoadWAV("erro.wav");
	if (!sound) {
		printf("Wav: SDL error=%s\n", SDL_GetError());
		return false;
	}
	sound1 = Mix_LoadWAV("Bounce_block.wav");
	if (!sound1) {
		printf("Wav: SDL error=%s\n", SDL_GetError());
		return false;
	}
	sound2 = Mix_LoadWAV("Bounce_Wall.wav");
	if (!sound2) {
		printf("Wav: SDL error=%s\n", SDL_GetError());
		return false;
	}
	nope = Mix_LoadWAV("GroundSound.wav");
	if (!sound2) {
		printf("Wav: SDL error=%s\n", SDL_GetError());
		return false;
	}
	/*Bounce_Block = Mix_LoadWAV("Bounce_Block");
	if(!Bounce_Block) {
		printf("Wav: SDL error=%s\n", SDL_GetError());
		return false;
	}
	Bounce_Wall = Mix_LoadWAV("Bounce_Wall.wav");
	if (!sound) {
		printf("Wav: SDL error=%s\n", SDL_GetError());
		return false;
	}
	Cosmo_Music = Mix_LoadMUS("Cosmo_Music.wav");
	if (!sound) {
		printf("Wav: SDL error=%s\n", SDL_GetError());
		return false;
	}*/
		
	
    return success;
}

SDL_Surface* loadSurface( char *path ) {
    /*The final optimized image*/
    SDL_Surface* optimizedSurface = NULL;

    /*Load image at specified path*/
    SDL_Surface* loadedSurface = IMG_Load( path );
    if( loadedSurface == NULL ) {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError() );
    }
    else {
        /*Convert surface to screen format*/
        optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, 0 );
        if( optimizedSurface == NULL ) {
            printf( "Unable to optimize image %s! SDL Error: %s\n", path, SDL_GetError() );
        }

        /*Get rid of old loaded surface*/
        SDL_FreeSurface( loadedSurface );
    }

    return optimizedSurface;
}

int loadMedia() {
    /*Loading success flag*/
    bool success = true;
    
    /*Load PNG surface*/
    gJPGSurface = loadSurface( "./ball.png" );
    if( gJPGSurface == NULL ) {
        printf( "Failed to load image! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    gJPGplatform = loadSurface( "./plataforma1.png" );
    if( gJPGplatform == NULL ) {
        printf( "Failed to load image! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    gJPGbloco0 = loadSurface( "./block1.png" );
    if( gJPGbloco0 == NULL ) {
        printf( "Failed to load image! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    gJPGbloco1 = loadSurface( "./block12.png" );
    if( gJPGbloco1 == NULL ) {
        printf( "Failed to load image! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    gJPGbloco2 = loadSurface( "./block13.png" );
    if( gJPGbloco2 == NULL ) {
        printf( "Failed to load image! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    gJPGbloco3 = loadSurface( "./block14.png" );
    if( gJPGbloco3 == NULL ) {
        printf( "Failed to load image! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    gJPGbloco4 = loadSurface( "./block15.png" );
    if( gJPGbloco4 == NULL ) {
        printf( "Failed to load image! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    gJPGbloco5 = loadSurface( "./block16.png" );
    if( gJPGbloco5 == NULL ) {
        printf( "Failed to load image! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    gJPGcoracao = loadSurface( "./coracao1.jpeg" );
    if( gJPGcoracao == NULL ) {
        printf( "Failed to load image! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    gJPGredbar = loadSurface( "./redbar.jpeg" );
    if( gJPGredbar == NULL ) {
        printf( "Failed to load image! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    gJPGgreenbar = loadSurface( "./greenbar.jpeg" );
    if( gJPGgreenbar == NULL ) {
        printf( "Failed to load image! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
	SDL_SetColorKey( gJPGSurface, SDL_TRUE, SDL_MapRGB( gScreenSurface->format, 
                              0x00, 0x00, 0x00 ));
    SDL_SetColorKey( gJPGplatform, SDL_TRUE, SDL_MapRGB( gScreenSurface->format, 
                              0x00, 0x00, 0x00 ));
    //Open the font
	gFont = TTF_OpenFont( "arcade.ttf", 50 );
	if( gFont == NULL )
	{
		printf( "Failed to load arcade font! SDL_ttf Error: %s\n", TTF_GetError() );
                return false;
	}
	gFont1 = TTF_OpenFont( "arcade.ttf", 180 );
	if( gFont1 == NULL )
	{
		printf( "Failed to load arcade font! SDL_ttf Error: %s\n", TTF_GetError() );
                return false;
	}
	gFont2 = TTF_OpenFont( "arcade.ttf", 110 );
	if( gFont2 == NULL )
	{
		printf( "Failed to load arcade font! SDL_ttf Error: %s\n", TTF_GetError() );
                return false;
	}
	
	
    return success;
}

void closing() {
    /*Free loaded image*/
    SDL_FreeSurface( gJPGSurface );
    gJPGSurface = NULL;
    free(font_texture);
    
    //Free global font
	TTF_CloseFont( gFont );
	gFont = NULL;

    /*Destroy window*/
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    /*Quit SDL subsystems*/
    IMG_Quit();
    SDL_Quit();
    TTF_Quit();
}
