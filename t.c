#include<ncurses.h>
#include"tetris.h"
#include"render.h"

int main(void) {
	initscr();
	cbreak();
	initialize_vars();
	draw_board();

	refresh();
	getch();
	endwin();
	return 0;
}
