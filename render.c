#include <ncurses.h>
#include "render.h"

int MAX_X, MAX_Y;
int mid;
void init_rinfo()
{
	getmaxyx(stdscr, MAX_Y, MAX_X);
	mid = (MAX_X - WIDTH) / 2;
	mvprintw(MAX_Y/2, mid, "HELLOWORLDHELLOWORLD");

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
	for (int i = 0; i < HEIGHT; i++)
		draw_hor(mid, i, WIDTH, "`", 1);
	draw_hor(mid, HEIGHT - 1, WIDTH, "=", 1);
	draw_hor(mid, HEIGHT, WIDTH, "/\\", 2);
	draw_ver(mid - 1, 0, HEIGHT, ">!");
	draw_ver(mid + WIDTH, 0, HEIGHT, "!<");
}

    

