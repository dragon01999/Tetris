#include <stdio.h>
#include <ncurses.h>
#include <errno.h>
#include <string.h>
#include "game_logic.h"
#include "render.h"
#include "score.h"

void update_scores(void)
{
    if (tetris.total_cleared / 10 >= tetris.level) {
		tetris.level += 1;
	}
	switch(tetris.cleared_lines) {
		case SINGLE:
		    tetris.score += 40 * (tetris.level + 1);
			break;
		case DOUBLE:
			tetris.score += 100 * (tetris.level + 1);
			break;
		case TRIPLE:
			tetris.score += 300 * (tetris.level + 1);
			break;
		case TETRIS:
			tetris.score += 1200 * (tetris.level + 1);
			break;
		default:
			break;
	}
	return;
}

void print_scores_lvl(void)
{
	attron(COLOR_PAIR(BOARD_COLOR));
	mvprintw(0, 0, "Score:%d ", tetris.score);
	mvprintw(2, 0, "Level:%d ", tetris.level);
	mvprintw(4, 0, "Lines cleared:%d", tetris.total_cleared);
	attroff(COLOR_PAIR(BOARD_COLOR));
	return;
}

void load_score(int *highest_score)
{
	FILE *in_file = fopen("Tetris.score", "r");
	if (!in_file) {
		if (errno != ENOENT) {
			fprintf(stderr,"File could'nt open. Error:%s\n", strerror(errno));
		}
		return;
	}
	if (fscanf(in_file, "%d", highest_score) == 1) {
		/*
		 *
		 */
	} else
		fprintf(stderr, "Error when reading from file");
	fclose(in_file);
	return;
}

void store_score(int highest_score)
{
	FILE *in_file = fopen("Tetris.score", "w");
        if (!in_file) {
		if (errno != ENOENT) {
			fprintf(stderr,"File could'nt open. Error:%s\n", strerror(errno));
		}
        return;
        }
	fprintf(in_file,"%d",highest_score);
	fclose(in_file);
	return;
}
