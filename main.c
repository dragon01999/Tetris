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
	init_BoardInfo();
	srand(time(NULL));
	tetro tetromino, tmp;
	rand_tetro(&tetromino);
	bool coll = false;
	int c = 0;
	for (int i = 0; i < 1000; i++) {
//		input(&tetromino);
		keypressed(&tetromino);
		tmp = tetromino;
		update_y(&tmp);
		c = is_coll(tmp);
		if (c == 0)
			tetromino = tmp;
		if (c == 1 || c == 2) {
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

