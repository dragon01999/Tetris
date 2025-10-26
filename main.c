#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "tetris.h"
#include "render.h"
#include "input.h"

bool game_status = true;
int main(int argc, char **argv) {

	init_curses();
	init_BoardInfo();
	srand(time(NULL));
	tetro tetromino, tmp;
	generate_tetromino(&tetromino);
	bool coll = false;
	while (game_status) {
		tmp = tetromino;
//		keypressed(&tmp);
		update_y(&tmp);
		if(!is_coll(tmp))                                         tetromino = tmp;
		else {
            store_tetromino(tetromino);
            generate_tetromino(&tetromino);
		}
		keypressed(&tetromino);
		clear_row();
		draw_board();
		draw_tetro(tetromino);
		print_stored_tetromino();
		refresh();
		getch();
		napms(400);
		clear();
	}
		
	endwin();
	return 0;
}

