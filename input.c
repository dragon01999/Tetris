#include <ncurses.h>
#include "tetris.h"

void input(tetro *tet)
{
	int ch;
	ch = getch();
	switch(ch) {
		case KEY_RIGHT:
			update_x(tet,2);
			break;
		case KEY_LEFT:
			update_x(tet, -2);
			break;
		case KEY_UP:
			update_y(tet);
			break;
		default:
			break;
	}
	return;
}
