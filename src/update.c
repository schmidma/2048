#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


void updateStats(SDL_Surface* window_surface, TTF_Font* font, int highscore, int points) {
	char *str_cpy;
	str_cpy = (char *)malloc(20 * sizeof(char));

	SDL_Rect stats_rect = { 470, 50, 140, 200 };
	SDL_Rect highscore_rect = { 470, 50, 140, 50 };
	SDL_Rect points_rect = { 470, 150, 140, 50 };
	SDL_Rect time_rect;
	SDL_Color textColor = { 100, 200, 100 };

	/* Clear Stats */
	SDL_FillRect(window_surface, &stats_rect, SDL_MapRGB(window_surface->format, 0, 0, 0));


	SDL_BlitSurface(TTF_RenderText_Solid(font, "Highscore:", textColor), NULL, window_surface, &highscore_rect);
	SDL_BlitSurface(TTF_RenderText_Solid(font, "Points:", textColor), NULL, window_surface, &points_rect);

	sprintf(str_cpy, "%d", highscore);
	highscore_rect.x += 10;
	highscore_rect.y += 50;
	SDL_BlitSurface(TTF_RenderText_Solid(font, str_cpy, textColor), NULL, window_surface, &highscore_rect);

	sprintf(str_cpy, "%d", points);
	points_rect.x += 10;
	points_rect.y += 50;
	SDL_BlitSurface(TTF_RenderText_Solid(font, str_cpy, textColor), NULL, window_surface, &points_rect);
}

/*
updateSurface()
//TODO!!
*/
void updateSurface(SDL_Window* window, int fields[], int dimension, int points, int highscore, TTF_Font* font_regular, TTF_Font* font_bold) {

	int x, y;
	int color = 255;
	int coord_x = 0;
	int coord_y = 0;

	if (points > highscore) {
		highscore = points;
	}

	SDL_Surface* window_surface = SDL_GetWindowSurface(window);
	SDL_Surface* text_surface;
	SDL_Color textColor = { 100, 200, 100 };

	SDL_Rect field_rect;
	SDL_Rect text_rect = { 0,0,0,0 };

	char *number_str;
	number_str = (char *)malloc(20 * sizeof(char));

	for (x = 0; x < dimension; x++) {

		coord_x = x * 105 + 25;

		for (y = 0; y < dimension; y++) {
			coord_y = y * 105 + 25;

			field_rect.x = coord_x;
			field_rect.y = coord_y;
			field_rect.w = 100;
			field_rect.h = 100;

			if (fields[y*dimension + x] != 0) {
				color = fields[y*dimension + x] * 10;
			}
			else {
				color = 255;
			}

			SDL_FillRect(window_surface, &field_rect, SDL_MapRGB(window_surface->format, color, color, color));

			if (fields[y*dimension + x] != 0) {
				sprintf(number_str, "%d", fields[y*dimension + x]);

				if (fields[y*dimension + x] < 10000) {
					text_surface = TTF_RenderText_Solid(font_bold, number_str, textColor);
				}
				else {
					text_surface = TTF_RenderText_Solid(font_regular, number_str, textColor); /* Anpassung der Schriftart bzw Gr��e bei 5-Stelligen Werten */
				}

				text_rect.x = field_rect.x + ((field_rect.w + text_surface->w) / 2 - text_surface->w);
				text_rect.y = field_rect.y + ((field_rect.h + text_surface->h) / 2) - text_surface->h;

				SDL_BlitSurface(text_surface, NULL, window_surface, &text_rect);
			}
		}
	}

	updateStats(window_surface, font_regular, highscore, points);

	SDL_UpdateWindowSurface(window);
}
