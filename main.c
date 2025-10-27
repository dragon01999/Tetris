#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "tetris.h"
#include "render.h"
#include "input.h"
#include "score.h"

bool game_status = true;
int main(int argc, char **argv) {

	init_curses();
	init_BoardInfo();
	srand(time(NULL));
	tetro tetromino, tmp;
	generate_tetromino(&tetromino);
	int score, level;
	score = level = 0;
	while (game_status) {
		keypressed(&tetromino);
		if (!tetromino_fall(&tetromino)) { 
		store_tetromino(tetromino);
                clear_row();
		update_scores(&score, &level);
		print_scores_lvl(score, level);
		clean_next();
		generate_tetromino(&tetromino); 
		}
		draw_board();        
		print_stored_tetromino();
		clean_tetromino(tetromino, "`");
		draw_tetro(tetromino, curr_piece);
		print_next_tetromino();
		refresh();
		napms(300);
	}
		
	endwin();
	return 0;
}

