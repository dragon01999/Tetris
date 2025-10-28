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
        int score, level;
        score = level = 0;
		nodelay(stdscr, FALSE);
		test(15);
        print_stored_tetromino();
		refresh();
		getch();
		clear_row();
		print_stored_tetromino();
		clear();
		printw("used clear_rogghghfffgggw");
		refresh();
/**""*"***"*†********/
		test(18);                                             print_stored_tetromino();                             refresh();                                            getch();                                              clear_row();
		clear();
		print_stored_tetromino();                                                                                  printw("used clear_row");                             refresh();
        getch();
		test(19);                                             print_stored_tetromino();                             refresh();                                            getch();                                              clear_row();                                          clear();                                              print_stored_tetromino();                                                                                  printw("used clear_row");                             refresh();
		getch();
		endwin();
        return 0;
}
