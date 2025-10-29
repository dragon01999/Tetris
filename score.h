#ifndef SCORE_H
#define SCORE_H

#define SINGLE 1
#define DOUBLE 2
#define TRIPLE 3
#define TETRIS 4

void update_scores(int *score, int *lvl);

void print_scores_lvl(int score, int lvl);

void load_score(int *highest_score);

void store_score(int highest_score);

#endif
