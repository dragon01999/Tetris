#include "tetris.h"
#inlcude "render.h'

table game_board[HEIGHT][WIDTH];
static tetro tetromino[7][4] = {
	[I] = {
		//0
		{ .x = {0, 2, 4, 6}, .y = {1, 1, 1, 1} .color = RED; },
		//90
		{ .x = {4, 4, 4, 4}, .y = {0, 1, 2, 3} },
		//180
		{ .x = {0, 2, 4, 6}, .y = {2, 2, 2, 2} },
		//270
		{ .x = {2, 2, 2, 2}, .y = {0, 1, 2, 3} }

	},
	[O] = {
		{ .x = {0, 2, 0, 2}, .y = {0, 0, 1, 1} }
	},


void rand_tetro(tetro tet)
{
	init_rinfo();
//	shape sh = (rand() % 7);
	tet = tetromino[1][0];
	return;
}

void rotate_tetro(tetro tet, int curr_r)
{
	int curr_x, curr_y, mid_x, mid_y;
	mid_x = tetromino[sh][1].x[1];
	mid_y = tetromino[sh][1].y[1];
	curr_x = tet.x[1];
	curr_y = tet.y[1];
	for (int i = 0; i < 4; i++) {
		tet.x[i] = (tetromino[sh][1].x[i] - mid_x) + curr_x;
		tet.y[i] = (tetromino[sh][1].y[i] - mid_y) + curr_y;
	}
}

void update_GameBoard(tetro tet)
{
	for (int i = 0; i < 4; i++) 
		game_board[tet.y[i]][tet.x[i]] = true;
	return;
}

void update_y(tetro tet)
{
	for (int i = 0; i < 4; i++)
		tet.y[i]++;
	return;
}

void update_x(tetro tet, int dir)
{
	for (int i = 0; i < 4; i++)
		tet.x[i] += dir;
	return;
}

bool is_coll(tetro tet)
{
	for (int i = 0; i < 4; i++) 
		if (tet.y[i] >= HEIGHT || game_board[tet.y[i]][tet.x[i]])
			return true;
	return false;
}

void blocks_inBoard()
{
	for (int i = 0; i < HEIGHT; i++)
		for (int k = 0; k < WIDTH; k++)
			if(game_board[i][k])
				mvprintw(i, k, "[]");
	return;
}



