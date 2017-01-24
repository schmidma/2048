#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


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