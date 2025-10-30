#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "render.h"
#include "tetris.h"

struct timespec start;
long long end_ms, curr_ms;
float delay = 400;

bool parse_input(tetro *tet)
{
	tetro tmp = *tet;
	int ch;
	bool overlap = false;
	ch = getch();
	switch(ch) {
		case KEY_RIGHT:
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
			if (curr_piece == O) {
				break;
			}
			rot = (rot + 1) % 4;
			rotate_tetromino(&tmp, rot);
			if (!is_colliding(tmp)) {
				if (!is_overlapping(&tmp)) {
				   *tet = tmp;
				}
				overlap = true;
			}
			break;
		case KEY_DOWN:
			move_down(&tmp);
			if (!is_colliding(tmp) && !is_overlapping(&tmp))
				*tet = tmp;
			else if (is_overlapping(&tmp))
				overlap = true;
			break;
		case 'p':
			// disable nodelay so getch() waits
			nodelay(stdscr, FALSE);

			do {
    // maybe print "Press P to continue..."
				} while (getch() != 'p');
			nodelay(stdscr, TRUE);
			break;
		case 'q':
			exit(1);

		default:
			break;
	}
	return overlap;
}

bool input(tetro *tetromino)
{
	tetro tmp;
	clock_gettime(CLOCK_MONOTONIC, &start);
	end_ms = (start.tv_sec * 1000) + delay  + (start.tv_nsec/1000000);
curr_ms = start.tv_sec * 1000 + (start.tv_nsec / 1000000);
    while (curr_ms <= end_ms) {
		clock_gettime(CLOCK_MONOTONIC, &start);
		curr_ms =  start.tv_sec * 1000 + (start.tv_nsec / 1000000);
        tmp = *tetromino;
	    parse_input(tetromino);
		clean_tetromino(tmp, "``");
		flushinp();
	    draw_tetro(*tetromino, curr_piece);
		refresh();
		napms(1);
	}
	return false;
}

