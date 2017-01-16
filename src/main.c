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

int main(int argc, char* args[]) {

    //INITIALIZE VARIABLES
    int round = 0;
    int points = 0;
    int fields[DIMENSION][DIMENSION] = {0};
    int quit = 0;
    SDL_Event event;

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf( stderr, "Could not initialise SDL: %s\n", SDL_GetError() );
        exit(-1);
    }
    else {
        printf("SDL_Init was successful!\n");
    }

    SDL_Window *screen = SDL_CreateWindow("2048", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL);

    print_fields(fields);
    
    while (!quit) {
        while( SDL_PollEvent( &event ) ){
            switch( event.type ){
                case SDL_KEYDOWN:
                    printf( "Key press detected\n" );
                    switch( event.key.keysym.sym ){
                        case SDLK_LEFT:
                            //LEFT
                            spawn_rand_field(fields);
                            print_fields(fields);
                            break;
                        case SDLK_RIGHT:
                            //RIGHT
                            break;
                        case SDLK_UP:
                            //UP
                            break;
                        case SDLK_DOWN:
                            //DOWN
                            break;
                        case SDLK_ESCAPE:
                            SDL_Quit();
                            exit(EXIT_SUCCESS);
                        default:
                            break;
                    }
                    break;
                    
                case SDL_QUIT:
                    SDL_Quit();
                    exit(EXIT_SUCCESS);
                    break;
                default:
                    break;
            }
        }
    }

    SDL_Quit();

    return 0;
}
