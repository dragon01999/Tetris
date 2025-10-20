#include <ncurses.h>
#include "tetris.h"

void input()
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
			upadate_y(tet, 1);
			break;
		default:
			break;
	}
	return;
}
