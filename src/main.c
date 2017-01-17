//
//  main.c
//  2048
//
//  Created by Maximilian Schmidt and Björn Bargstädt
//  Copyright © 2017 Maximilian Schmidt and Björn Bargstädt. All rights reserved.
//

/* INCLUDE */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "move.h"

/*
 spawn_rand_field(int[], int)
 Parameter: fields, dimension

 Fügt an einem zufällig gewähltem freien Feld eine "2" (nmbr) ein.
 */
void spawn_rand_field(int fields[], int dimension) {
    int nmbr = 2;
    int x,y;
    int free = 0;
    int *freeFields[dimension*dimension];

    for (x = 0; x < dimension; x++) {
        for (y = 0; y < dimension; y++) {
            if (fields[dimension*y+x] == 0) {
                freeFields[free] = &(fields[dimension*y+x]);
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


/*
 print_fields(int[], int)
 Parameter: fields, dimension

 Gibt die Zahlen der Felder aus
 */
void print_fields(int fields[], int dimension) {
    int a,b;
    for (a = 0; a < dimension; a++) {
        printf("\n");
        for (b = 0; b < dimension; b++) {
            printf("%d\t", fields[dimension*b+a]);
        }
    }
    printf("\n");
}


/*
 updateSurface(SDL_Renderer*, int)
 Parameter: renderer, dimension

 Aktualisiert die Anzeige-Oberfläche
  - Erstellt einzelne Quadrate
  - Zeigt die Quadrate an
 */
void updateSurface(SDL_Renderer* renderer, int dimension){
	int a,b;
	int x=0;
	int y=0;

	for(a=0; a<dimension; a++){

        x=a*105+25;

		for(b=0; b<dimension; b++){
			y=b*105+25;

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

void createSurface(SDL_Renderer* renderer, int dimension) {
    SDL_SetRenderDrawColor(renderer, 255,255,255, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	SDL_Rect box = {20,20,425,425};
	SDL_SetRenderDrawColor(renderer, 0,0,0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(renderer, &box);

}

/*
 print_FieldsOnScreen(int[], int)
 Parameter: fields, dimension
 */
void print_FieldsOnScreen(int fields[], int dimension) {}

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

const int FPS = 24;
const int SCREENW = 640;
const int SCREENH = 480;

int main(int argc, char* args[]) {

    /* INITIALIZE VARIABLES */
    int round = 0;
    int points = 0;
    int dimension = 4;
    int run = 1;
    int *fields;

    Uint32 lastTick;
    Uint32 currentTick;
    int sleep;
    double period = 1.0 / (double)FPS * 1000;
    int milliPeriod = (int)period;

    fields = (int*)calloc(dimension*dimension, sizeof(int));
    if (fields == NULL) {
        printf("Fehler bei calloc....\n");
        return EXIT_FAILURE;
    }

    /* SDL VARIABLES */
    SDL_Event event;

    init_SDL();

    SDL_Window* screen = SDL_CreateWindow("2048", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREENW, SCREENH, SDL_WINDOW_OPENGL);
	SDL_Renderer* renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);

	createSurface(renderer, dimension);

    print_fields(fields, dimension);

    while (run) {
        lastTick = SDL_GetTicks();

        while( SDL_PollEvent( &event ) ){
            switch( event.type ){
                case SDL_KEYDOWN:
                    /* ON KEYPRESS */
                    switch( event.key.keysym.sym ){
                        case SDLK_LEFT:
                            /* LEFT */

                            break;
                        case SDLK_RIGHT:
                            /* RIGHT */

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
            updateSurface(renderer, dimension);


        }
        currentTick = SDL_GetTicks();

        sleep = milliPeriod - (currentTick - lastTick);
        if (sleep < 0) sleep = 0;
        SDL_Delay(sleep);
        printf("%d\n", sleep);
    }

    SDL_Quit();

    return 0;
}
