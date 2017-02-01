#include <stdio.h>
#include <stdlib.h>


int* openHighscore() {
	FILE *highscoreFile;
	highscoreFile = fopen("highscore.txt", "r");
	int *highscore;
	int checksum = 42;
	int checksum_read = 0;

	highscore = (int*)calloc(6, sizeof(int));
	if (highscore == NULL) {
		fprintf(stderr, "Cannot allocate memory!!\n");
		exit(EXIT_FAILURE);
	}

	if (highscoreFile == NULL) {
		fprintf(stderr, "Cannot open highscore.txt!\n");
		fclose(highscoreFile);
		return (int*)highscore;
	}
	else {
		printf("Read Highscore...\n");

		for (int i = 0; i < 6; i++) {
			fscanf(highscoreFile, "%d", &(highscore[i]));
			checksum += highscore[i];
		}

		fscanf(highscoreFile, "%d", &checksum_read);

		if (checksum_read != checksum) {
			fprintf(stderr, "Highscorefile damaged!\n");
			exit(EXIT_FAILURE);
		}

		fclose(highscoreFile);
		return (int*)highscore;
	}
}

void writeHighscore(int points, int *highscore_list, int gametype) {
	FILE *highscoreFile;
	int checksum = 0;
	highscore_list[gametype - 4] = points;

	highscoreFile = fopen("highscore.txt", "w+");

	for (int i = 0; i < 6; i++) {
		checksum += highscore_list[i];
		fprintf(highscoreFile, "%d ", highscore_list[i]);
	}

	checksum += 42;

	fprintf(highscoreFile, "%d\n", checksum);

	fclose(highscoreFile);
	free(highscore_list);
}