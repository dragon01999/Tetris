#include<ncurses.h>
#include"tetris.h"
#include"render.h"

int main(void) {
	initscr();
	cbreak();
	tetris tet[2];
	init_tetromino(tet, 0, S);
	initialize_vars();
	draw_board();

	while(!collision(tet, 0)) {
		update('y', tet, 0);
		draw_tetromino(tet, 0);
		draw_board();
		refresh();
		napms(400);
		clear();
	}

	refresh();
	getch();
	endwin();
	return 0;
}
