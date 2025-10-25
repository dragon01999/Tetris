#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "tetris.h"

struct timespec start;
long long end_ms, curr_ms;
float wait_ms = 100;

void input(tetro *tet)
{
	tetro tmp = *tet;
	int ch;
	ch = getch();
	switch(ch) {
		case KEY_RIGHT:
			beep();
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
			rotate_tetromino(&tmp, curr_rot);
			if (!is_coll(tmp))
                *tet = tmp;
			break;
		default:
			break;
	}
	return;
}

void keypressed(tetro *tetromino)
{
	clock_gettime(CLOCK_MONOTONIC, &start);
	end_ms = (start.tv_sec * 1000) + 10  + (start.tv_nsec/1000000);
curr_ms = start.tv_sec * 1000 + (start.tv_nsec / 1000000);
	while (curr_ms <= end_ms) {
		clock_gettime(CLOCK_MONOTONIC, &start);
		curr_ms =  start.tv_sec * 1000 + (start.tv_nsec / 1000000);
		input(tetromino);
	}
	return;
}


