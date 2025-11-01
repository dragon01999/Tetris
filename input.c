#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "render.h"
#include "tetris.h"

#if WITH_SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#endif

struct timespec start;
long long end_ms, curr_ms;
float delay = 800;

bool parse_input(tetro *tet)
{
	tetro tmp = *tet;
	int ch = getch();
	if (ch != ERR)
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
				if (tetris.curr_piece == O) {
					break;
				}
				tetris.rotation = (tetris.rotation + 1) % 4;
				rotate_tetromino(&tmp);
				if (!is_colliding(tmp)) {
					if (!is_overlapping(&tmp)) {
						*tet = tmp;
					}
					return false;
				}
				break;
			case KEY_DOWN:
				move_down(&tmp);
				if (!is_colliding(tmp) && !is_overlapping(&tmp))
					*tet = tmp;
				else if (is_overlapping(&tmp))
					return false;
				break;
			case ' ':
				hard_drop(tet);
				tetris.score += 10;
				/* return false so that we spawn new piece */
				return false;
			case 'p':
			/* disable nodelay so getch() waits */
				nodelay(stdscr, FALSE);
				#if WITH_SDL
				Mix_PauseMusic();
				#endif
				do {
					/*
					 * Just loop until p is pressed
					 */
				} while (getch() != 'p');
				#if WITH_SDL
				Mix_ResumeMusic();
				#endif
				nodelay(stdscr, TRUE);
				break;
			case 'q':
				tetris.game_status = false;
				return false;

			default:
				break;
	}
	return true;
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
	    if (!parse_input(tetromino)) {
			return true;
		}
		/* for clean we are using " `" cuz the position of left '[' will always be ' ' */
		clean_tetromino(tmp, " `");
		flushinp();
	    draw_tetro(*tetromino, tetris.curr_piece);
		refresh();
		napms(2);
	}
	return false;
}

