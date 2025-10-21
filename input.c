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
			update_x(&tmp, -2);
			if (!is_coll(tmp))
				*tet = tmp;
			break;
		case KEY_UP:
			curr_rot = (curr_rot + 1) % 4;
			rotate_tetro(tet, curr_rot);
			break;
		default:
			break;
	}
	return;
}
