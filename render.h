/* for rendering board and other function related to ascii art */
#ifndef RENDER_H
#define RENDER_H

#include "tetris.h"
// WIDTH is 20 cuz each block in a tetromino is depicted using []
#define BOARD_WIDTH 20
#define BOARD_HEIGHT 20
extern int MAX_X, MAX_Y;

extern int left_x; //left side wall
extern int right_x; //right side wall 

void init_BoardInfo();

void draw_hor(int x, int y, int times, char *obj, int obj_len);

void draw_ver(int x, int y, int times, char *obj);

void draw_board();

void draw_tetro(tetro tet);

#endif
