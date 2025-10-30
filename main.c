#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "tetris.h"
#include "render.h"
#include "input.h"
#include "score.h"

int main(int argc, char **argv) {

        init_curses();
        init_BoardInfo();
        srand(time(NULL));
        tetro tetromino;
        generate_tetromino(&tetromino);
        int score, level, highest_score;
        score = highest_score = 0;
		level = 1;
		tetris.game_status = true;
		print_keys();
        while (tetris.game_status) {
			print_scores_lvl(score, level);
			draw_logo();
			draw_board();
            print_stored_tetromino();
            draw_tetro(tetromino, tetris.curr_piece);
            print_next_tetromino();
			refresh();
			input(&tetromino);
            if (!tetromino_fall(&tetromino)) {
				if (is_game_over(&tetromino))
					tetris.game_status = false;
                store_tetromino(tetromino);
                clear_row();
                update_scores(&score, &level);
                print_scores_lvl(score, level);
                clean_next();
				refresh();
                generate_tetromino(&tetromino); 
                }
        }
		clear();
		nodelay(stdscr, FALSE);
		load_score(&highest_score);
		if (score > highest_score) {
			printw("Congratulations! you have beaten the highest score: %d. Current highest:%d", highest_score, score);
			store_score(score);
		} else
		    printw("Highest Score: %d", highest_score);
		getch();
        endwin();
        return 0;
}
