/* for rendering board and other function related to ascii art */
#ifndef RENDER_H
#define RENDER_H

#include "tetris.h"
// WIDTH is 20 cuz each block in a tetromino is depicted using []
#define BOARD_WIDTH 20
#define BOARD_HEIGHT 20

#define COLOR_ORANGE 208
#define BOARD_COLOR 4
#define I_PIECE 0
#define O_PIECE 1
#define J_PIECE 2
#define L_PIECE 3
#define S_PIECE 4
#define Z_PIECE 5
#define T_PIECE 6


extern int MAX_X, MAX_Y;

extern int left_x; //left side wall
extern int right_x; //right side wall 

void init_curses();

void init_BoardInfo();

void draw_hor(int x, int y, int times, char *obj, int obj_len);

void draw_ver(int x, int y, int times, char *obj);

void draw_board();

void draw_tetro(tetro tet);

#endif
