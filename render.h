/* for rendering board and other function related to ascii art */
#ifndef RENDER_H
#define RENDER_H

// HEIGHT is 20 cuz each block in a tetromino is depicted using []
#define WIDTH 20
#define HEIGHT 20
extern int MAX_X, MAX_Y;


void init_rinfo();
void draw_hor(int x, int y, int times, char *obj, int obj_len);
void draw_ver(int x, int y, int times, char *obj);
void draw_board();
#endif
