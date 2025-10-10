#ifndef TETRIS_H
#define TETRIS_H
#include<stdbool.h>
#include<stdint.h>
#include"input.h"

typedef struct tetris {
	uint8_t x[4];
	uint8_t y[4];
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

void init_tetromino(tetris *arr, int index);

void placeIn_Mid(tetris *arr, int pos);

void update_GameBoard(tetris *tet, int in);
	
bool collision(tetris *tet, int in);

void update_y(tetris *tet, int in);

void update_x(tetris *tet, int in, int dir);

void tetromino_fall(tetris *tet, int in);

void draw_game();

#endif
