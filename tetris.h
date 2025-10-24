#ifndef TETRIS_H
#define TETRIS_H
#include <stdint.h>

#define HEIGHT 20 //DIMENSIONS OF GAMEBOARD
#define WIDTH 10 

typedef struct tetro {
	int x[4];
	int y[4];
} tetro;

typedef struct table {
	bool block;
} table;

typedef enum {
	I = 0,
	O = 1,
	J = 2,
	L = 3,
	S = 4,
	Z = 5,
	T = 6,
} shape;

typedef enum {
	LEFT_WALL = 0,
	RIGHT_WALL = 1,
	BOTTOM = 2,
	TOP = 3,
	BLOCK_FELL = 4
} collision;
	
extern shape curr_shape;

extern int curr_rot;

void place_InMid(tetro *tet);

void rand_tetro(tetro *tet);

void rotate_tetro(tetro *tet, int curr_r);

void store_tetromino(tetro tet);

void update_y(tetro *tet);

void update_x(tetro *tet, int dir);

int is_coll(tetro tet);

void blocks_inBoard();

void tetromino_fall(tetro *tet, float ms);

bool is_rowFull(int row);

void update_Boardblock();
#endif
		
