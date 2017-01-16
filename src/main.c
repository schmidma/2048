//
//  main.c
//  2048
//
//  Created by Maximilian Schmidt on 15/01/2017.
//  Copyright © 2017 Maximilian Schmidt. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>

#define DIMENSION 4

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

void m_down (int fields[DIMENSION][DIMENSION]) {
    int x,y;

    for (y = 0; y < DIMENSION-1; y++) {
        for (x = 0; x < DIMENSION; x++) {
            if (fields[x][y+1] == fields[x][y]) {
                fields[x][y] = fields[x][y]*2;
                fields[x][y+1] = 0;
            }
        }
    }
}

void m_up (int fields[DIMENSION][DIMENSION]) {}

void m_left (int fields[DIMENSION][DIMENSION]) {}

void m_right (int fields[DIMENSION][DIMENSION]) {}


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

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const char* WINDOW_TITLE = "SDL Start";

int main(int argc, char* args[]) {

    //INITIALIZE VARIABLES
    int round = 0;
    int points = 0;
    int fields[DIMENSION][DIMENSION] = {0};
    int quit = 0;
    SDL_Event event;

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
        fprintf( stderr, "Could not initialise SDL: %s\n", SDL_GetError() );
        exit(-1);
    else
        printf("SDL_Init was successful!\n");

    if (!SDL_SetVideoMode( WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0)) {
        fprintf( stderr, "Could not set video mode: %s\n", SDL_GetError() );
            SDL_Quit();
            exit( -1 );
    }

    SDL_EnableUNICODE( 1 );

    while (!quit) {
            while(SDL_PollEvent(&event)) {
                    switch( event.type ){
                    /* Keyboard event */
                    /* Pass the event data onto PrintKeyInfo() */
                    case SDL_KEYDOWN:
                    case SDL_KEYUP:
                        //TODO: keyInfo: https://www.libsdl.org/release/SDL-1.2.15/docs/html/guideinputkeyboard.html
                        //PrintKeyInfo( &event.key );
                        break;

                    /* SDL_QUIT event (window close) */
                    case SDL_QUIT:
                        quit = 1;
                        break;

                    default:
                        break;
                }
            }
    }

    SDL_Quit();

    return 0;
}
