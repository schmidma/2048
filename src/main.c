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


/*
 updateSurface(SDL_Renderer*, int)
 Parameter: renderer, dimension

 Aktualisiert die Anzeige-Oberfläche
  - Erstellt einzelne Quadrate
  - Zeigt die Quadrate an
 */
void updateSurface(SDL_Window* window, int fields[], int dimension){
	int x, y;
	int color = 255;
	int coord_x = 0;
	int coord_y = 0;
	SDL_Surface* surface = SDL_GetWindowSurface(window);
	SDL_Surface* text;
	SDL_Color textColor = {100,200,100};
	TTF_Font* font = TTF_OpenFont("src/OpenSans-Bold.ttf",36);
	TTF_Font* font_high = TTF_OpenFont("src/OpenSans-Regular.ttf",30);
	char *number_str;
	number_str = (char *)malloc(20*sizeof(char));

	for(x = 0; x < dimension; x++){

        coord_x = x*105+25;

		for(y = 0; y < dimension; y++){
			coord_y = y*105+25;

			SDL_Rect rect;
			rect.x = coord_x;
			rect.y = coord_y;
			rect.w = 100;
			rect.h = 100;

			if (fields[y*dimension + x] != 0) {
				color = fields[y*dimension + x] * 10;
			}
			else {
				color = 255;
			}

			SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, color, color, color));
			if(font==NULL){
				fprintf(stderr, "Font nicht gefunden");
			}
			else{
				if(fields[y*dimension+x]!=0){
					sprintf(number_str, "%d", fields[y*dimension + x]);
					if(fields[y*dimension+x]<10000){
						text = TTF_RenderText_Solid(font, number_str, textColor);
					}
					else{
						text = TTF_RenderText_Solid(font_high, number_str, textColor); //Anpassung der Schriftart bzw Größe bei 5-Stelligen Werten
					}
					SDL_Rect dst = {rect.x+((rect.w+text->w)/2-text->w),rect.y+((rect.h+text->h)/2)-text->h,0,0};
					SDL_BlitSurface(text,NULL,surface,&dst);
				}
			}
		}
	}
	SDL_UpdateWindowSurface(window);
	TTF_CloseFont(font);
}


const int FPS = 24;
const int SCREENW = 640;
const int SCREENH = 480;

void createSurface(SDL_Window* window) {
	SDL_Rect box = {20,20,425,425};
	SDL_Surface* surface = SDL_GetWindowSurface(window);
	SDL_FillRect(surface, &box, SDL_MapRGB(surface->format, 255, 255, 255));
	SDL_UpdateWindowSurface(window);
}

int openHighscore() {
	FILE *highscoreFile;
	highscoreFile = fopen("highscore.txt", "r");
	int highscore;

	if (highscoreFile == NULL) {
		fprintf(stderr, "Cannot open highscore.txt!\n");
		fclose(highscoreFile);
		return 0;
	}
	else {
		printf("Read Highscore...\n");
		fscanf(highscoreFile, "%d", &highscore);
		printf("highscore: %d\n", highscore);
		fclose(highscoreFile);
		return highscore;
	}
}

void writeHighscore(int points) {
	FILE *highscoreFile;
	highscoreFile = fopen("highscore.txt", "w");

	fprintf(highscoreFile, "%d", points);
	fclose(highscoreFile);
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

void init_SDL() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Could not initialise SDL: %s\n", SDL_GetError());
        exit(-1);
    }
    else {
        printf("SDL_Init was successful!\n");
    }
}

void init_TTF() {
    if(TTF_Init() == -1) {
        fprintf(stderr, "Could not initialise TTF: %s\n", SDL_GetError());
        exit(-1);
    }
    else {
        printf("TTF_Init was successful!\n");
    }
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

	printf("\n\n------------------------------------\nWelcome to 2048!\n------------------------------------\n\n");
	printf("INITIALIZE...\n");
    init_SDL();
	init_TTF();
	printf("\n");

	highscore = openHighscore();

    SDL_Window* screen = SDL_CreateWindow("2048", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREENW, SCREENH, SDL_WINDOW_OPENGL);

	createSurface(screen);

	spawn_rand_field(fields, dimension);
	updateSurface(screen, fields, dimension);

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
        if (moved) {
            updateSurface(screen, fields, dimension);
        }

        currentTick = SDL_GetTicks();

        sleep = milliPeriod - (currentTick - lastTick);
        if (sleep < 0) sleep = 0;
        SDL_Delay(sleep);
    }

    SDL_Quit();

    return 0;
}
