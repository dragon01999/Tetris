#include<ncurses.h>
#include<stdio.h>
#include<string.h>
#include"tetris.h"
#include"render.h"

int MAX_X, MAX_Y;
int border_x, border_y;
int init_x, init_y, mid;

void initialize_vars()
{
	getmaxyx(stdscr, MAX_Y, MAX_X);
	init_x = (MAX_X/4) + 1; // 1 is offset
	init_y = 0;
	mid = init_x + (width / 2);
	border_x = init_x + width;
	border_y = init_y + height;
}

void draw_x(int x_pos, int y_pos, int times, char *str, int str_len)
{
	for (int x = x_pos; x < (x_pos + times); x += str_len) {
		mvprintw(y_pos, x, "%s", str);
	}
	return;
}


void draw_y(int x_pos, int y_pos, int times, char *str, int str_len)
{
    for (int y = y_pos; y < (y_pos + times); y += str_len) {
        mvprintw(y, x_pos, "%s", str);
    }
    return;
}

void draw_board()
{   
	draw_y(init_x, init_y, height, "<!", 1);
    draw_x(init_x + 2, border_y - 1, width - 1, "=", 1);
    draw_x(init_x + 1, border_y, width, "/\\", 2);
    draw_y(border_x, init_y, height, "!>", 1);
}

void draw_tetromino(tetris *arr, int in)
{
	for (int i = 0; i < 4; i++) {
		mvprintw(arr[in].y[i], arr[in].x[i], "[]");
	}
	return;
}

