#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "render.h"
#include "tetris.h"

struct timespec start;
long long end_ms, curr_ms;
float delay = 400;

bool input(tetro *tet)
{
	tetro tmp = *tet;
	int ch;
	bool overlap = false;
	ch = getch();
	switch(ch) {
		case KEY_RIGHT:
			beep();
			move_direction(&tmp,2);
			if (!is_colliding(tmp) && !is_overlapping(&tmp))
				*tet = tmp;
			break;
		case KEY_LEFT:
			move_direction(&tmp, -2);
			if (!is_colliding(tmp) && !is_overlapping(&tmp))
				*tet = tmp;
			break;
		case KEY_UP:
			curr_rot = (curr_rot + 1) % 4;
			rotate_tetromino(&tmp, curr_rot);
			if (!is_colliding(tmp))
				if (!is_overlapping(&tmp))
				   *tet = tmp;
				overlap = true;
			break;
		case KEY_DOWN:
			move_down(&tmp);
			if (!is_colliding(tmp) && !is_overlapping(&tmp))
				*tet = tmp;
			else if (is_overlapping(&tmp))
				overlap = true;
			break; 
		case 'q':
			exit(1);
		default:
			break;
	}
	return overlap;
}

bool keypressed(tetro *tetromino)
{
	tetro tmp;
	clock_gettime(CLOCK_MONOTONIC, &start);
	end_ms = (start.tv_sec * 1000) + delay  + (start.tv_nsec/1000000);
curr_ms = start.tv_sec * 1000 + (start.tv_nsec / 1000000);
    while (curr_ms <= end_ms) {
		clock_gettime(CLOCK_MONOTONIC, &start);
		curr_ms =  start.tv_sec * 1000 + (start.tv_nsec / 1000000);
               tmp = *tetromino;
		clean_tetromino(tmp, "``");
	    input(tetromino);
		flushinp();
	    draw_tetro(*tetromino, curr_piece);
		refresh();
		napms(100);
//		tmp = *tetromino;
	}
	return false;
}

