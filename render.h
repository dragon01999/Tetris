/* for rendering board and other function related to ascii art */
#ifndef RENDER_H
#define RENDER_H

#include "tetris.h"
// WIDTH is 20 cuz each block in a tetromino is depicted using []
#define BOARD_WIDTH 20
#define BOARD_HEIGHT 20

#define BOARD_COLOR 8

struct ScreenInfo {
	int max_y;
	int max_x;
	int left_wall;
	int right_wall;
};

extern struct ScreenInfo screen;

void init_curses(void);

void init_BoardInfo(void);

void draw_logo(void);

void print_keys(void);

void draw_board(void);

void draw_tetro(tetro tet, int piece);

void clean_tetromino(tetro tet, char *str);

void print_stored_tetromino(void);

void print_next_tetromino(void);

void clean_next(void);

void screen_to_logic(tetro *tet);

void logic_to_screen(tetro *tet);

void place_in_mid(tetro *tet);

#endif
