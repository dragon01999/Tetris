/* File dedicated for testing & debugging. */
#include<stdio.h>
#include<string.h>
#include<ncurses.h>
#include"render.h"

int main(int argc, char *argv[]) {
	initscr();
	cbreak();
	printw("Hello, world!");
    draw_x(14, 5, 20, "=", 1);	
    refresh();
	getch();
	endwin();
	return 0;
}

