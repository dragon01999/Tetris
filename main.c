#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "tetris.h"
#include "render.h"
#include "input.h"

int main(int argc, char **argv) {

	init_curses();
	init_BoardInfo();
	srand(time(NULL));
	tetro tetromino, tmp;
	generate_tetromino(&tetromino);
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
			generate_tetromino(&tetromino);
		}
		clear_row();
		draw_board();
		draw_tetro(tetromino);
		print_stored_tetromino();
		refresh();
		getch();
		napms(300);
		clear();
	}
		
	endwin();
	return 0;
}

