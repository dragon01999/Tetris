#include<ncurses.h>
#include<stdio.h>
#include<string.h>
#include"render.h"

int MAX_X, MAX_Y;
int border_x, border_y;
int initial_x, initial_y;

void intialize_vars()
{
	getmaxyx(stdscr, MAX_X, MAX_Y);
	initial_x = (MAX_X/4) + 1; // 1 is offset
	initial_y = 1;
	border_x = initial_x + width;
	border_y = initial_y + height;
}

void draw_x(int x_pos, int y_pos, int times, char *str, int str_len)
{
	for (int x = x_pos; x < (x_pos + times); x += str_len) {
		mvprintw(y_pos, x, "%s", str);
	}
	return;
}
