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

#include "../include/move.h"
#include "../include/highscore.h"
#include "../include/init.h"
#include "../include/update.h"


/*
 spawn_rand_field(int[], int)
 Parameter: fields, dimension

 Fügt an einem zufällig gewähltem freien Feld eine "2" (nmbr) ein.
 */
void spawn_rand_field(int fields[], int dimension) {
    int nmbr = 2;
    int x, y;
    int free = 0;
    int *freeFields[dimension*dimension];

    for (x = 0; x < dimension; x++) {
        for (y = 0; y < dimension; y++) {
            if (fields[dimension*y+x] == 0) {
                freeFields[free] = &(fields[dimension*y + x]);
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
    int x, y;
    for (y = 0; y < dimension; y++) {
        printf("\n");
        for (x = 0; x < dimension; x++) {
            printf("%d\t", fields[y*dimension + x]);
        }
    }
    printf("\n");
}

int getGametime(clock_t starttime) {
	int t = ((long)clock() - (long)starttime) / 1000;
	return t;
}

/*
 quit()

 Beendet das Programm
 */
void quit(int points, int highscore) {
	printf("\nEXIT Game...\n");
	printf("Check for new Highscore.\n");
	if (points > highscore) {
		printf("Write new Highscore(%d).\n", points);
		writeHighscore(points);
	}

	TTF_Quit();
    SDL_Quit();
	printf("\nQUIT\n");
    exit(EXIT_SUCCESS);
}


int main(int argc, char* args[]) {

    /* INITIALIZE VARIABLES */
    int round = 0;
    int points = 0;
    int dimension = 4;
    int run = 1;
    int *fields;
    int moved = 0;
	int highscore;
	clock_t starttime = clock();

	const int FPS = 24;
	const int SCREENW = 105*dimension+220;
	const int SCREENH = 105*dimension+60;

    Uint32 lastTick;
    Uint32 currentTick;
    int sleep;
    double period = 1.0 / (double)FPS * 1000;
    int milliPeriod = (int)period;

    fields = (int*)calloc(dimension*dimension, sizeof(int));
    if (fields == NULL) {
        fprintf(stderr, "Fehler bei calloc....\n");
        return EXIT_FAILURE;
    }

    /* SDL VARIABLES */
    SDL_Event event;

	TTF_Font* font_regular;
	TTF_Font* font_bold;

	printf("\n\n------------------------------------\nWelcome to 2048!\n------------------------------------\n\n");
	printf("INITIALIZE...\n");

    init_SDL();
	init_TTF();

	font_regular = loadFont("ttf/OpenSans-Regular.ttf", 30);
	font_bold = loadFont("ttf/OpenSans-Bold.ttf", 36);
	
	printf("\n");

	highscore = openHighscore();

    SDL_Window* screen = SDL_CreateWindow("2048", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREENW, SCREENH, SDL_WINDOW_OPENGL);

	//createSurface(screen);

	spawn_rand_field(fields, dimension);
	updateSurface(screen, fields, dimension, points, highscore, font_regular, font_bold, getGametime(starttime));

    while (run) {
        moved = 0;
        lastTick = SDL_GetTicks();

        while( SDL_PollEvent( &event ) ){
            switch( event.type ){
                case SDL_KEYDOWN:
                    /* ON KEYPRESS */
                    switch( event.key.keysym.sym ){
                        case SDLK_LEFT:
                            /* LEFT */
							if ((moved = m_left(fields, dimension, &points))) {
								spawn_rand_field(fields, dimension);
							}
                            break;
                        case SDLK_RIGHT:
                            /* RIGHT */
							if ((moved = m_right(fields, dimension, &points))) {
								spawn_rand_field(fields, dimension);
							}
                            break;
                        case SDLK_UP:
                            /* UP */
							if ((moved = m_up(fields, dimension, &points))) {
								spawn_rand_field(fields, dimension);
							}
                            break;
                        case SDLK_DOWN:
                            /* DOWN */
							if ((moved = m_down(fields, dimension, &points))) {
								spawn_rand_field(fields, dimension);
							}
                            break;
                        case SDLK_ESCAPE:
                            quit(points, highscore);
                            break;
                        default:
                            break;
                    }
                    break;

                case SDL_QUIT:
                    quit(points, highscore);
                    break;
                default:
                    break;
            }
        }
        
        updateSurface(screen, fields, dimension, points, highscore, font_regular, font_bold, getGametime(starttime));
        
        currentTick = SDL_GetTicks();

        sleep = milliPeriod - (currentTick - lastTick);
        if (sleep < 0) sleep = 0;
        SDL_Delay(sleep);
    }

    SDL_Quit();

    return 0;
}
