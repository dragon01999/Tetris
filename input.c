#include<stdlib.h>
#include<ncurses.h>
#include"tetris.h"
#include"input.h"

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
//			rotate_tetris(tet);
			break;
		case KEY_DOWN:
		//	set_napms(100);
			break;
//		case q:
		//	GAME_STATUS = false;
//			break;
		default:
			/*
			 * Do nothing
			 */
			break;
	}
	return;
}

		
			
