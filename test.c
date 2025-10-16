/* File dedicated for testing & debugging. */
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ncurses.h>
#include<time.h>
#include"render.h"
#include"tetris.h"
int main(int argc, char *argv[]) {
        initscr();
        cbreak();
		keypad(stdscr, TRUE);
          	nodelay(stdscr, TRUE);
		srand(time(NULL));
    tetris pieces[2];
	init_tetromino(pieces, 0);
	initialize_vars();

	//for (int i = 0; i < 30; i++) {
		tetromino_fall(pieces, 0);
		draw_game();
		draw_board();
		draw_tetromino(pieces, 0);
		refresh();
		for (int i = 0; i < 8; i++) {
		init_tetromino(pieces, 1);
		tetromino_fall(pieces, 1);
        draw_game();
        draw_board();
		draw_tetromino(pieces, 0);
        draw_tetromino(pieces, 1);
		refresh();
		}
		//}
    nodelay(stdscr, FALSE);
	getch();
	endwin();
	return 0;
}

