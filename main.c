#include <stdio.h>
#include <ncurses.h>
#include "tetris.h"
#include "render.h"
#include "input.h"

int main(int argc, char **argv) {
	initscr();
	cbreak();
	keypad(stdscr, TRUE);
	init_rinfo();
	tetro tetromino, tmp;
	rand_tetro(&tetromino);
	bool coll = false;
	for (int i = 0; i < 20; i++) {
		tmp = tetromino;
		input(&tmp);
		update_y(&tmp);
		coll = is_coll(tmp);
		if (!coll)
			tetromino = tmp;
		if (coll)
			break;
		draw_tetro(tetromino);
		draw_board();
		blocks_inBoard();
		refresh();
		getch();
		napms(300);
		clear();
	}
		
	endwin();
	return 0;
}

