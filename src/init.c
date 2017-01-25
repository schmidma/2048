#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>


void init_SDL() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "Could not initialise SDL: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	else {
		printf("SDL_Init was successful!\n");
	}
}


void init_TTF() {
	if (TTF_Init() == -1) {
		fprintf(stderr, "Could not initialise TTF: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	else {
		printf("TTF_Init was successful!\n");
	}
}

void init_IMG(){
	int flags = IMG_INIT_PNG;
	if(!(IMG_Init(flags) & flags)){
		fprintf(stderr,"Could not initialise IMAGE: %s\n", IMG_GetError() );
        exit(EXIT_FAILURE);
    }
	else{
		printf("IMG_Init was successful!\n");
	}
}

TTF_Font* loadFont(char* ttf, int size) {
	TTF_Font* font = TTF_OpenFont(ttf, size);
	
	if (font == NULL) {
		fprintf(stderr, "Font %s not found!\n", ttf);
		exit(EXIT_FAILURE);
	}
}

void createSurface(SDL_Window* window) {
	SDL_Rect box = { 20,20,425,425 };
	SDL_Surface* surface = SDL_GetWindowSurface(window);
	SDL_FillRect(surface, &box, SDL_MapRGB(surface->format, 255, 255, 255));
	SDL_UpdateWindowSurface(window);
}