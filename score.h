#ifndef SCORE_H
#define SCORE_H

#define SINGLE 1
#define DOUBLE 2
#define TRIPLE 3
#define TETRIS 4

void update_scores(void);

void print_scores_lvl(void);

void load_score(int *highest_score);

void store_score(int highest_score);

#endif
