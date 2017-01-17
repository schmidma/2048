//
//  main.c
//  2048
//
//  Created by Maximilian Schmidt on 15/01/2017.
//  Copyright © 2017 Maximilian Schmidt. All rights reserved.
//


/* INCLUDE */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

/* MAKRO */

#define DIMENSION 4

/*
 spawn_rand_field(int [][])
 Parameter: fields
 
 Fügt an einem zufällig gewähltem freien Feld eine "2" (nmbr) ein.
 */
void spawn_rand_field(int fields[DIMENSION][DIMENSION]) {
    int nmbr = 2;
    int x,y;
    int free = 0;
    int *freeFields[DIMENSION*DIMENSION];

    for (x = 0; x < DIMENSION; x++) {
        for (y = 0; y < DIMENSION; y++) {
            if (fields[x][y] == 0) {
                freeFields[free] = &(fields[x][y]);
                free++;
            }
        }
    }

    if (!free) {
        printf("GAMEOVER!!!!\n");
        exit(EXIT_SUCCESS);
    }

    srand((unsigned int)time(NULL));
    *freeFields[rand() % free] = nmbr;
}


/* MOVE */
void m_down (int fields[DIMENSION][DIMENSION]) {}
void m_up (int fields[DIMENSION][DIMENSION]) {}
void m_left (int fields[DIMENSION][DIMENSION]) {}
void m_right (int fields[DIMENSION][DIMENSION]) {}


/*
 print_fields(int [][])
 Parameter: fields
 
 Gibt die Zahlen der Felder aus
 */
void print_fields(int fields[DIMENSION][DIMENSION]) {
    int a,b;
    for (a = 0; a < DIMENSION; a++) {
        printf("\n");
        for (b = 0; b < DIMENSION; b++) {
            printf("%d\t", fields[a][b]);
        }
    }
    printf("\n");
}


/*
 updateSurface(SDL_Renderer*)
 Parameter: renderer
 
 Aktualisiert die Anzeige-Oberfläche
  - Erstellt einzelne Quadrate
  - Zeigt die Quadrate an
 */
void updateSurface(SDL_Renderer* renderer){
	int a,b;
	int x=0;
	int y=0;
    
	for(a=0; a<DIMENSION; a++){
		
        x=a*100+20;
        
		for(b=0; b<DIMENSION; b++){
			y=b*100+20;
            
			SDL_Rect rect;
			rect.x=x;
			rect.y=y;
			rect.w=100;
			rect.h=100;
            
			int c=b*20+a*10;
            
			SDL_SetRenderDrawColor(renderer, c, c, c, SDL_ALPHA_OPAQUE);
            
			SDL_RenderFillRect(renderer, &rect);
		}
	}
	SDL_RenderPresent(renderer);
}

/*
 print_FieldsOnScreen(int [][])
 Parameter: fields
 */
void print_FieldsOnScreen(int fields[DIMENSION][DIMENSION]) {}

/*
 quit()
 
 Beendet das Programm
 */
void quit() {
    SDL_Quit();
    exit(EXIT_SUCCESS);
}

void init_SDL() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf( stderr, "Could not initialise SDL: %s\n", SDL_GetError() );
        exit(-1);
    }
    else {
        printf("SDL_Init was successful!\n");
    }
}

int main(int argc, char* args[]) {

    /* INITIALIZE VARIABLES */
    int round = 0;
    int points = 0;
    int fields[DIMENSION][DIMENSION] = {0};
    int run = 1;
    
    /* SDL VARIABLES */
    SDL_Event event;
    
    /* TEXT VARIABLES
    SDL_Surface* wsurface;
    SDL_Surface* text_surface;
	TTF_Font* tfont;
    SDL_Color tcolor = {.r = 105, .g = 200, .b = 30, .a = 200};
    SDL_Rect blit_position;
     */

    init_SDL();

    SDL_Window* screen = SDL_CreateWindow("2048", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL);
	SDL_Renderer* renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);

    print_fields(fields);
    
    while (run) {
        while( SDL_PollEvent( &event ) ){
            switch( event.type ){
                case SDL_KEYDOWN:
                    /* ON KEYPRESS */
                    
                    switch( event.key.keysym.sym ){
                        case SDLK_LEFT:
                            /* LEFT */
                            
                            spawn_rand_field(fields);
                            print_fields(fields);
                            
                            break;
                        case SDLK_RIGHT:
                            /* RIGHT */
                            
							/* TEXT
                            srand((unsigned int)time(NULL));
							wsurface = SDL_GetWindowSurface(screen);
							text_surface = TTF_RenderText_Solid(TTF_STYLE_BOLD, "TEST", tcolor);
							blit_position.x = rand()%500;
							blit_position.y = rand()%300;
							blit_position.w = 100;
							blit_position.h = 100;
							SDL_BlitSurface(text_surface, NULL, wsurface, blit_position);
							SDL_FreeSurface(text_surface);
							SDL_UpdateWindowSurface(screen);
                             */
                            
                            break;
                        case SDLK_UP:
                            /* UP */
                            
                            break;
                        case SDLK_DOWN:
                            /* DOWN */
                            
                            break;
                        case SDLK_ESCAPE:
                            quit();
                            break;
                        default:
                            break;
                    }
                    break;
                    
                case SDL_QUIT:
                    quit();
                    break;
                default:
                    break;
            }
        }
        updateSurface(renderer);
    }

    SDL_Quit();

    return 0;
}
