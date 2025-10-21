#include <ncurses.h>
#include "tetris.h"

void input(tetro *tet)
{
	tetro tmp = *tet;
	int ch;
	ch = getch();
	switch(ch) {
		case KEY_RIGHT:
			update_x(&tmp,2);
			if (!is_coll(tmp))
				*tet = tmp;
			break;
		case KEY_LEFT:
			update_x(tet, -2);
			break;
		case KEY_UP:
			rotate_tetro(tet, 1);
			break;
		default:
			break;
	}
	return;
}
