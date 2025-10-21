#ifndef TETRIS_H
#define TETRIS_H
#include <stdint.h>
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

extern shape curr_shape;

void place_InMid(tetro *tet);

void rand_tetro(tetro *tet);

void rotate_tetro(tetro *tet, int curr_r);

void store_tetromino(tetro tet);

void update_y(tetro *tet);

void update_x(tetro *tet, int dir);

bool is_coll(tetro tet);

void blocks_inBoard();

bool is_rowTrue(int row);

void update_Boardblock();
#endif
		
