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

void createSurface(SDL_Rect* rect[DIMENSION][DIMENSION], SDL_Renderer* renderer){
	
	int a,b;
	int x=0;
	int y=0;
	for(a=0; a<DIMENSION; a++){
		x=a*100+20;
		for(b=0; b<DIMENSION; b++){
			y=b*100+20;
			SDL_Rect rtoDraw;
			rtoDraw.x=x;
			rtoDraw.y=y;
			rtoDraw.w=100;
			rtoDraw.h=100;
			rect[a][b]=&rtoDraw;
			int c=b*20+a*10;
			SDL_SetRenderDrawColor(renderer, c, c, c, SDL_ALPHA_OPAQUE);
			SDL_RenderFillRect(renderer, rect[a][b]);
			SDL_RenderPresent(renderer);
		}
	}
	
}

/*void print_FieldsOnScreen(int fields[DIMENSION][DIMENSION]){
	int a,b;
	
}*/

void quit() {
    SDL_Quit();
    exit(EXIT_SUCCESS);
}

int main(int argc, char* args[]) {

    //INITIALIZE VARIABLES
    int round = 0;
    int points = 0;
    int fields[DIMENSION][DIMENSION] = {0};
	SDL_Rect* surface[DIMENSION][DIMENSION];
    int run = 1;
    SDL_Event event;

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf( stderr, "Could not initialise SDL: %s\n", SDL_GetError() );
        exit(-1);
    }
    else {
        printf("SDL_Init was successful!\n");
    }

    SDL_Window* screen = SDL_CreateWindow("2048", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL);
	SDL_Renderer* renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);
	
	createSurface(surface,renderer);
	
	SDL_SetRenderDrawColor(renderer, 100, 200, 150, SDL_ALPHA_OPAQUE);

    print_fields(fields);
    
    while (run) {
        while( SDL_PollEvent( &event ) ){
            switch( event.type ){
                case SDL_KEYDOWN:
                    printf( "Key press detected\n" );
                    switch( event.key.keysym.sym ){
                        case SDLK_LEFT:
                            //LEFT
                            spawn_rand_field(fields);
                            print_fields(fields);
							
							srand((unsigned int)time(NULL));
							SDL_RenderDrawLine(renderer, rand()%640, rand()%480, rand()%640, rand()%480);
							SDL_RenderPresent(renderer);
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
    }

    SDL_Quit();

    return 0;
}
