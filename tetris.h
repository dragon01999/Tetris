#ifndef TETRIS_H
#define TETRIS_H
#include <stdint.h>
typedef struct tetro {
	int x[4];
	int y[4];
	uint_8h color;
} tetro;

typedef struct table {
	bool block;
	uint_8h color;
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

void rand_tet(tetro tet);

#endif
		
