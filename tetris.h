#ifndef TETRIS_H
#define TETRIS_H

typedef struct tetris {
	int x[4];
	int y[4];
}tetris;

typedef enum {
	I = 0,
	O = 1,
	T = 2,
	S = 3,
	Z = 4,
	J = 5,
	L = 6,
} tetromino;

extern tetromino curr_tetromino;


void init_tetromino(tetris *arr, int index, tetromino s);

void placeIn_Mid(tetris *arr);

void update_y(tetris *arr);

#endif
