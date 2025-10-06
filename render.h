/* Renders ascii art, such as the board, tetromino and
 * other art related functions. */
#ifndef RENDER_H
#define RENDER_H

#include"tetris.h"
// Game board size
#define width 20
#define height 20

extern int MAX_X, MAX_Y;
// Intial X & Y within game window
extern int init_x, init_y, mid;
// Border of game
extern int border_x, border_y;

/* str_len is to increment x/y coordinate with respect to strings size. */
void draw_x(int x_pos, int y_pos, int times, char *str, int str_len);

void draw_y(int x_pos, int y_pos, int times, char *str, int str_len);

void initialize_vars();

void draw_board();
                                                      void draw_tetromino(tetris *arr);




#endif
