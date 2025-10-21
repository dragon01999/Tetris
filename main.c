#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "tetris.h"
#include "render.h"
#include "input.h"

int main(int argc, char **argv) {
	initscr();
	cbreak();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	init_rinfo();
	srand(time(NULL));
	tetro tetromino, tmp;
	rand_tetro(&tetromino);
	bool coll = false;
	for (int i = 0; i < 1000; i++) {
		tmp = tetromino;
		input(&tmp);
		update_y(&tmp);
		coll = is_coll(tmp);
		if (!coll)
			tetromino = tmp;
		if (coll) {
			store_tetromino(tetromino);
			rand_tetro(&tetromino);
		}
		update_Boardblock();
		draw_board();
		draw_tetro(tetromino);
		blocks_inBoard();
		refresh();
		getch();
		napms(300);
		clear();
	}
		
	endwin();
	return 0;
}

