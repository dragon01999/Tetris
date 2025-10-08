#include<stdlib.h>
#include<ncurses.h>
#include"tetris.h"

void input(tetris *tet)
{
	int ch = getch();
	switch(ch) {
		case RIGHT:
			update_x(tet, 1);
			break;
		case LEFT:
			update_x(tet, -1);
			break;
		case UP:
			rotate_tetris(tet);
			break;
		case DOWN:
			set_napms(100);
			break;
		case q:
			GAME_STATUS = false;
			break;
		default:
			/*
			 * Do nothing
			 */
			break;
	}
	return;
}

		
			
