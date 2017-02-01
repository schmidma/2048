#include <stdio.h>
#include <stdlib.h>


/* MOVE */
int m_up (int fields[], int dimension, int *points, int move) {
    //printf("MOVE_M_UP\n");
	int x, y, y2;
	int moved = 0;
	for (y = 0; y < dimension; y++) {
		for (x = 0; x < dimension; x++) {
			if (fields[y*dimension + x] != 0) {
				//printf("DETECTED: %d auf (%d, %d)\n", fields[y*dimension + x], x, y);
				for (y2 = y+1; y2 < dimension; y2++) {
					if (fields[y2*dimension + x] != 0) {
						//printf("2nd DETECTED: %d auf (%d, %d)\n", fields[y2*dimension + x], x, y2);
						if (fields[y2*dimension + x] == fields[y*dimension + x]) {
							//printf("MERGE!\n");
							if (move) {
								fields[y*dimension + x] = fields[y*dimension + x] * 2;
								fields[y2*dimension + x] = 0;
								*points += fields[y*dimension + x];
							}
							moved = 1;
						}
						break;
					}
				}
				//printf("\n");
			}
		}
	}
	for (y = 0; y < dimension; y++) {
		for (x = 0; x < dimension; x++) {
			if (fields[y*dimension + x] == 0) {
				for (y2 = y + 1; y2 < dimension; y2++) {
					if (fields[y2*dimension + x] != 0) {
						//printf("MOVE: %d from (%d, %d) to (%d, %d)\n", fields[y2*dimension + x], x, y2, x, y);
						if (move) {
							fields[y*dimension + x] = fields[y2*dimension + x];
							fields[y2*dimension + x] = 0;
							//printf("\n");
						}
						moved = 1;
						break;
					}
				}
			}
		}
	}
	return moved;
}

int m_down(int fields[], int dimension, int *points, int move) {
	//printf("MOVE_M_DOWN\n");
	int x, y, y2;
	int moved = 0;
	for (y = dimension-1; y >= 0; y--) {
		for (x = dimension-1; x >= 0; x--) {
			if (fields[y*dimension + x] != 0) {
				for (y2 = y - 1; y2 >= 0; y2--) {
					if (fields[y2*dimension + x] != 0) {
						if (fields[y2*dimension + x] == fields[y*dimension + x]) {
							if (move) {
								fields[y*dimension + x] = fields[y*dimension + x] * 2;
								fields[y2*dimension + x] = 0;
								*points += fields[y*dimension + x];
							}
							moved = 1;
						}
						break;
					}
				}
			}
		}
	}
	for (y = dimension - 1; y >= 0; y--) {
		for (x = dimension - 1; x >= 0; x--) {
			if (fields[y*dimension + x] == 0) {
				for (y2 = y - 1; y2 >= 0; y2--) {
					if (fields[y2*dimension + x] != 0) {
						if (move) {
							fields[y*dimension + x] = fields[y2*dimension + x];
							fields[y2*dimension + x] = 0;
						}
						moved = 1;
						break;
					}
				}
			}
		}
	}
	return moved;
}

int m_left(int fields[], int dimension, int *points, int move) {
	//printf("MOVE_M_LEFT\n");
	int x, y, x2;
	int moved = 0;
	for (y = 0; y < dimension; y++) {
		for (x = 0; x < dimension; x++) {
			if (fields[y*dimension + x] != 0) {
				for (x2 = x + 1; x2 < dimension; x2++) {
					if (fields[y*dimension + x2] != 0) {
						if (fields[y*dimension + x2] == fields[y*dimension + x]) {
							if (move) {
								fields[y*dimension + x] = fields[y*dimension + x] * 2;
								fields[y*dimension + x2] = 0;
								*points += fields[y*dimension + x];
							}
							moved = 1;
						}
						break;
					}
				}
			}
		}
	}
	for (y = 0; y < dimension; y++) {
		for (x = 0; x < dimension; x++) {
			if (fields[y*dimension + x] == 0) {
				for (x2 = x + 1; x2 < dimension; x2++) {
					if (fields[y*dimension + x2] != 0) {
						if (move) {
							fields[y*dimension + x] = fields[y*dimension + x2];
							fields[y*dimension + x2] = 0;
						}
						moved = 1;
						break;
					}
				}
			}
		}
	}
	return moved;
}

int m_right(int fields[], int dimension, int *points, int move) {
	//printf("MOVE_M_RIGHT\n");
	int x, y, x2;
	int moved = 0;
	for (y = dimension - 1; y >= 0; y--) {
		for (x = dimension - 1; x >= 0; x--) {
			if (fields[y*dimension + x] != 0) {
				for (x2 = x - 1; x2 >= 0; x2--) {
					if (fields[y*dimension + x2] != 0) {
						if (fields[y*dimension + x2] == fields[y*dimension + x]) {
							if (move) {
								fields[y*dimension + x] = fields[y*dimension + x] * 2;
								fields[y*dimension + x2] = 0;
								*points += fields[y*dimension + x];
							}
							moved = 1;
						}
						break;
					}
				}
			}
		}
	}
	for (y = dimension - 1; y >= 0; y--) {
		for (x = dimension - 1; x >= 0; x--) {
			if (fields[y*dimension + x] == 0) {
				for (x2 = x - 1; x2 >= 0; x2--) {
					if (fields[y*dimension + x2] != 0) {
						if (move) {
							fields[y*dimension + x] = fields[y*dimension + x2];
							fields[y*dimension + x2] = 0;
						}
						moved = 1;
						break;
					}
				}
			}
		}
	}
	return moved;
}



int checkgameover(int fields[], int dimension) {
	int moved = 0;

	moved += m_up(fields, dimension, NULL, 0);
	moved += m_down(fields, dimension, NULL, 0);
	moved += m_left(fields, dimension, NULL, 0);
	moved += m_right(fields, dimension, NULL, 0);

	return moved;
}
