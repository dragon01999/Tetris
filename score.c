#include <stdio.h>
#include "tetris.h"
#include "score.h"

void update_scores(int *score, int *lvl)
{
	if ((*lvl / 10) > lvl)
		*lvl++;
	switch(cleared_lines) {
		case SINGLE:
		    *score += 40 * (lvl + 1);
			break;
		case DOUBLE:
			*score += 100 * (lvl + 1);
			break;
		case TRIPLE:
			*score += 300 * (lvl + 1);
			break;
		case TETRIS:
			*score += 1200 * (lvl + 1);
			break;
		default:
			break;
	}
	return;
}


