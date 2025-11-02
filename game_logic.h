#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H
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

struct GameState {
	int curr_piece;
	int next;
	tetro next_tetromino;
	int rotation;
	int cleared_lines;
	int total_cleared;
	int score;
	int level;
	bool game_status;
};

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

extern table game_board[HEIGHT][WIDTH];
extern const tetro tetromino[7][4];
extern struct GameState tetris;

void generate_tetromino(tetro *tet);

void rotate_tetromino(tetro *tet);

void store_tetromino(tetro tet);

void move_down(tetro *tet);

void hard_drop(tetro *tet);

void move_direction(tetro *tet, int dir);

bool is_colliding(tetro tet);

bool is_overlapping(tetro *tet);

bool is_game_over(tetro *tet);

bool tetromino_fall(tetro *tet);

bool is_lineFull(int line);

void clear_lines(void);

#endif
		
