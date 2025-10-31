#include <stdio.h>
#include <ncurses.h>
#include <errno.h>
#include "tetris.h"
#include "render.h"
#include "score.h"

void update_scores(int *score, int *lvl)
{
    if (tetris.total_cleared / 10 >= *lvl)
		*lvl += 1;
	switch(tetris.cleared_lines) {
		case SINGLE:
		    *score += 40 * (*lvl + 1);
			break;
		case DOUBLE:
			*score += 100 * (*lvl + 1);
			break;
		case TRIPLE:
			*score += 300 * (*lvl + 1);
			break;
		case TETRIS:
			*score += 1200 * (*lvl + 1);
			break;
		default:
			break;
	}
	return;
}

void print_scores_lvl(int score, int lvl)
{
	attron(COLOR_PAIR(BOARD_COLOR));
	mvprintw(0, 0, "Score:%d ", score);
	mvprintw(2, 0, "Level:%d ", lvl);
	attroff(COLOR_PAIR(BOARD_COLOR));
}

void load_score(int *highest_score)
{
	FILE *in_file = fopen("Tetris.score", "r");
	if (!in_file) {
		if (errno != ENOENT)
			fprintf(stderr,"File could'nt open. Error:%s\n", strerror(errno));
		return;
	}
	if (fscanf(in_file, "%d", highest_score) == 1) {
		//
	} else
		fprintf(stderr, "Error when reading from file");
	fclose(in_file);
	return;
}

void store_score(int highest_score)
{
	FILE *in_file = fopen("Tetris.score", "w");
    if (!in_file) {
		if (errno != ENOENT) 
			fprintf(stderr,"File could'nt open. Error:%s\n", strerror(errno));
        return;
    }
	fprintf(in_file,"%d",highest_score);
	fclose(in_file);
}
