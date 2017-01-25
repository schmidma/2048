#include <stdio.h>
#include <stdlib.h>

int check_free(int fields[], int dimension){
    int x, y;
    int free = 0;

    for (x = 0; x < dimension; x++) {
        for (y = 0; y < dimension; y++) {
            if (fields[dimension*y+x] == 0) {
                free++;
				break;
            }
        }
    }

	return free;
}


/* MOVE */
int m_up (int fields[], int dimension, int *points) {
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
							fields[y*dimension + x] = fields[y*dimension + x] * 2;
							fields[y2*dimension + x] = 0;
							moved = 1;
							*points += fields[y*dimension + x];
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
						fields[y*dimension + x] = fields[y2*dimension + x];
						fields[y2*dimension + x] = 0;
						//printf("\n");
						moved = 1;
						break;
					}
				}
			}
		}
	}
	if (moved==0){
		if(check_free(fields,dimension)==0){printf("\n press R for restart!\n");}
	}
	return moved;
}

int m_down(int fields[], int dimension, int *points) {
	//printf("MOVE_M_DOWN\n");
	int x, y, y2;
	int moved = 0;
	for (y = dimension-1; y >= 0; y--) {
		for (x = dimension-1; x >= 0; x--) {
			if (fields[y*dimension + x] != 0) {
				for (y2 = y - 1; y2 >= 0; y2--) {
					if (fields[y2*dimension + x] != 0) {
						if (fields[y2*dimension + x] == fields[y*dimension + x]) {
							fields[y*dimension + x] = fields[y*dimension + x] * 2;
							fields[y2*dimension + x] = 0;
							moved = 1;
							*points += fields[y*dimension + x];
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
						fields[y*dimension + x] = fields[y2*dimension + x];
						fields[y2*dimension + x] = 0;
						moved = 1;
						break;
					}
				}
			}
		}
	}
	if (moved==0){
		if(check_free(fields,dimension)==0){printf("\n press R for restart!\n");}
	}
	return moved;
}

int m_left(int fields[], int dimension, int *points) {
	//printf("MOVE_M_LEFT\n");
	int x, y, x2;
	int moved = 0;
	for (y = 0; y < dimension; y++) {
		for (x = 0; x < dimension; x++) {
			if (fields[y*dimension + x] != 0) {
				for (x2 = x + 1; x2 < dimension; x2++) {
					if (fields[y*dimension + x2] != 0) {
						if (fields[y*dimension + x2] == fields[y*dimension + x]) {
							fields[y*dimension + x] = fields[y*dimension + x] * 2;
							fields[y*dimension + x2] = 0;
							moved = 1;
							*points += fields[y*dimension + x];
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
						fields[y*dimension + x] = fields[y*dimension + x2];
						fields[y*dimension + x2] = 0;
						moved = 1;
						break;
					}
				}
			}
		}
	}
	if (moved==0){
		if(check_free(fields,dimension)==0){printf("\n press R for restart!\n");}
	}
	return moved;
}

int m_right(int fields[], int dimension, int *points) {
	//printf("MOVE_M_RIGHT\n");
	int x, y, x2;
	int moved = 0;
	for (y = dimension - 1; y >= 0; y--) {
		for (x = dimension - 1; x >= 0; x--) {
			if (fields[y*dimension + x] != 0) {
				for (x2 = x - 1; x2 >= 0; x2--) {
					if (fields[y*dimension + x2] != 0) {
						if (fields[y*dimension + x2] == fields[y*dimension + x]) {
							fields[y*dimension + x] = fields[y*dimension + x] * 2;
							fields[y*dimension + x2] = 0;
							moved = 1;
							*points += fields[y*dimension + x];
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
						fields[y*dimension + x] = fields[y*dimension + x2];
						fields[y*dimension + x2] = 0;
						moved = 1;
						break;
					}
				}
			}
		}
	}
	if (moved==0){
		if(check_free(fields,dimension)==0){printf("\n press R for restart!\n");}
	}
	return moved;
}
