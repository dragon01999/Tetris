/* File dedicated for testing & debugging. */
#include<stdio.h>
#include<string.h>
#include<ncurses.h>
#include"tetris.h"
#include"render.h"

int main(int argc, char *argv[]) {
	initscr();
	cbreak();
    tetris pieces[2];
//	int x, y;
//	getmaxyx(stdscr, y, x);
//	mvprintw(24, 5, "y: %i, x: %i", y, x);
    init_tetromino(pieces, 0, J);
	init_tetromino(pieces, 1, I);
	initialize_vars();
	printw("Hello, world!");
    draw_tetromino(pieces, 0);
	draw_board();
	update(pieces, 0, 'y');
	refresh();
	update(pieces, 1, 'y');
	draw_tetromino(pieces, 0);
	refresh();
	getch();
	draw_tetromino(pieces, 1);
	refresh();
	getch();
	endwin();
	return 0;
}

