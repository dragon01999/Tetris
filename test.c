/* File dedicated for testing & debugging. */
#include<stdio.h>
#include<string.h>
#include<ncurses.h>
#include"render.h"

int main(int argc, char *argv[]) {
	initscr();
	cbreak();
	int x, y;
	getmaxyx(stdscr, y, x);
	mvprintw(24, 5, "y: %i, x: %i", y, x);
	initialize_vars();
	printw("Hello, world!");
	draw_board();
    refresh();
	getch();
	endwin();
	return 0;
}

