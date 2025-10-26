#ifndef TETRIS_H
#define TETRIS_H
#include <stdint.h>

/* dimensions of actual gameboard */
#define HEIGHT 20 
#define WIDTH 10 

/* struct to represent tetromino */
typedef struct tetro {
	int x[4];
	int y[4];
} tetro;

/* table aka matrix or board */
typedef struct table {
	bool block;
	uint8_t color;
} table;

/* tetromino shapes */
typedef enum {
	I = 0,
	O = 1,
	J = 2,
	L = 3,
	S = 4,
	Z = 5,
	T = 6,
} shape;

extern int curr_rot;
extern int next, curr_piece;

/* to place tetromino in middle */
void place_InMid(tetro *tet);

void generate_tetromino(tetro *tet);

void rotate_tetromino(tetro *tet, int curr_r);

void store_tetromino(tetro tet);

void update_y(tetro *tet);

void update_x(tetro *tet, int dir);

/* to detect collisions */
int is_coll(tetro tet);

void print_stored_tetromino();

void print_next_tetromino();
                                                      void clean_next();

bool tetromino_fall(tetro *tet);

bool is_row_full(int row);

void clear_row();

#endif
		
