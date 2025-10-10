#include<stdlib.h>
#include<ncurses.h>
#include"tetris.h"
#include"input.h"

static const tetris poss_rot[6][4];
void rotate_tetris(tetris *tet, int in)               {                                                         int m = 2; /* 3rd block as mid */                     tet[in].x[0] = tet[in].x[m] + 4;                      tet[in].x[1] = tet[in].x[m] + 2;                      tet[in].x[3] = tet[in].x[m] - 2;                                                                            tet[in].y[0] = tet[in].y[m] - 2;                      tet[in].y[1] = tet[in].y[m] - 1;                      tet[in].y[3] = tet[in].y[m] + 1;                                                                            return;
}

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
			rotate_tetris(tet, in);
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


			
