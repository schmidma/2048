#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


/*
updateSurface(SDL_Renderer*, int)
Parameter: renderer, dimension

Aktualisiert die Anzeige-Oberfläche
- Erstellt einzelne Quadrate
- Zeigt die Quadrate an
*/
void updateSurface(SDL_Window* window, int fields[], int dimension, int points, int highscore) {

	int x, y;
	int color = 255;
	int coord_x = 0;
	int coord_y = 0;

	if (points > highscore) {
		highscore = points;
	}

	SDL_Surface* surface = SDL_GetWindowSurface(window);
	SDL_Surface* text;
	SDL_Color textColor = { 100,200,100 };

	TTF_Font* font = TTF_OpenFont("ttf/OpenSans-Bold.ttf", 36);
	TTF_Font* font_high = TTF_OpenFont("ttf/OpenSans-Regular.ttf", 30);
	SDL_Rect dst = { 0,0,0,0 };
	SDL_Rect blank_highscore = { 470, 50, 140, 100 };
	SDL_Rect blank_points = { 470, 150, 140, 100 };

	if (font == NULL) {
		fprintf(stderr, "Font ttf/OpenSans-Bold.ttf not found!\n");
		exit(EXIT_FAILURE);
	}
	if (font_high == NULL) {
		fprintf(stderr, "Font ttf/OpenSans-Regular.ttf not found!\n");
		exit(EXIT_FAILURE);
	}

	char *number_str;
	char *time_str;
	time_str = (char *)malloc(10 * sizeof(char));
	number_str = (char *)malloc(20 * sizeof(char));

	for (x = 0; x < dimension; x++) {

		coord_x = x * 105 + 25;

		for (y = 0; y < dimension; y++) {
			coord_y = y * 105 + 25;

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

			if (fields[y*dimension + x] != 0) {
				sprintf(number_str, "%d", fields[y*dimension + x]);

				if (fields[y*dimension + x] < 10000) {
					text = TTF_RenderText_Solid(font, number_str, textColor);
				}
				else {
					text = TTF_RenderText_Solid(font_high, number_str, textColor); /* Anpassung der Schriftart bzw Größe bei 5-Stelligen Werten */
				}
				dst.x = rect.x + ((rect.w + text->w) / 2 - text->w);
				dst.y = rect.y + ((rect.h + text->h) / 2) - text->h;

				SDL_BlitSurface(text, NULL, surface, &dst);
			}
		}
	}


	SDL_FillRect(surface, &blank_highscore, SDL_MapRGB(surface->format, 0, 0, 0));
	SDL_FillRect(surface, &blank_points, SDL_MapRGB(surface->format, 0, 0, 0));
	SDL_BlitSurface(TTF_RenderText_Solid(font_high, "Highscore:", textColor), NULL, surface, &blank_highscore);
	SDL_BlitSurface(TTF_RenderText_Solid(font_high, "Points:", textColor), NULL, surface, &blank_points);

	sprintf(number_str, "%d", highscore);
	text = TTF_RenderText_Solid(font, number_str, textColor);
	dst.x = 500;
	dst.y = 100;

	SDL_BlitSurface(text, NULL, surface, &dst);

	sprintf(number_str, "%d", points);
	text = TTF_RenderText_Solid(font, number_str, textColor);
	dst.x = 500;
	dst.y = 200;

	SDL_BlitSurface(text, NULL, surface, &dst);

	SDL_UpdateWindowSurface(window);
	TTF_CloseFont(font);
}
