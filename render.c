#include <ncurses.h>
#include "render.h"

int MAX_X, MAX_Y;
int left_x, right_x;
void init_BoardInfo()
{
	getmaxyx(stdscr, MAX_Y, MAX_X);
	left_x = (MAX_X - BOARD_WIDTH) / 2;
	right_x = left_x + BOARD_WIDTH;
//	mvprintw(MAX_Y/2, mid, "HELLOWORLDHELLOWORLD");

}

void draw_hor(int x, int y, int times, char *obj, int obj_len)
{
	for (int i = 0; i < times; i += obj_len) 
		mvprintw(y, x + i, "%s", obj);
	
}

void draw_ver(int x, int y, int times, char *obj)
{
	for (int i = 0; i < times; i++)
		mvprintw(y + i, x, "%s", obj);
}

void draw_board()
{	
	for (int i = 0; i < BOARD_HEIGHT; i++)
		draw_hor(left_x, i, BOARD_WIDTH, "`", 1);
	draw_hor(left_x, BOARD_HEIGHT - 1, BOARD_WIDTH, "=", 1);
	draw_hor(left_x, BOARD_HEIGHT, BOARD_WIDTH, "/\\", 2);
	draw_ver(left_x - 1, 0, BOARD_HEIGHT, ">!");
	draw_ver(left_x + BOARD_WIDTH, 0, BOARD_HEIGHT, "!<");
}

void draw_tetro(tetro tet)
{
	for (int i = 0; i < 4; i++) {
		mvprintw(tet.y[i], tet.x[i], "[]");
	}
	return;
}
    

