#include<stdlib.h>
#include<ncurses.h>
#include"tetris.h"
#include"input.h"

static const tetris poss_rot[6][4];


void input(tetris *tet, int in)
{
	int ch = getch();
	switch(ch) {
		case KEY_RIGHT:
			update_x(tet, in, 2);
			break;
		case KEY_LEFT:
			update_x(tet, in, -2);
			break;
		case KEY_UP:
			rotate_tetris(tet, in, 1);
			break;
//		case KEY_DOWN:
//			break;
//		case 'q':

		default:
			/*
			 * Do nothing
			 */
			break;
	}
	return;
}


			
