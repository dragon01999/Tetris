#include <stdbool.h>
#include <stdlib.h>
#include <ncurses.h>
#include "tetris.h"
#include "render.h"

table game_board[HEIGHT][WIDTH];
table second_board[HEIGHT][WIDTH];
table *curr_board, *tmp_board;
int sh;
static tetro tetromino[7][4] = {
	[I] = {
		//0
		{ .x = {0, 2, 4, 6}, .y = {1, 1, 1, 1} },
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
	[J] = {                                                       { .x = {0,0,2,4}, .y = {0,1,2,2} },                   { .x = {0,2,2,2}, .y = {0,0,1,2} },                   { .x = {2,4,2,2}, .y = {0,0,1,2} },                   { .x = {0,2,4,4}, .y = {1,1,1,2} }            },                                                                                                          [L] = {                                                       { .x = {4,0,2,4}, .y = {0,1,1,1} },                   { .x = {2,2,2,4}, .y = {0,1,2,2} },                   { .x = {0,2,4,0}, .y = {1,1,1,2} },                   { .x = {0,2,2,2}, .y = {0,0,1,2} }            },                                                                                                          [S] = {                                                       { .x = {2,4,0,2}, .y = {0,0,1,1} },
		    { .x = {0,0,2,2}, .y = {0,1,1,2} },
	        { .x = {2,4,0,2}, .y = {1,1,2,2} },                   { .x = {2,2,4,4}, .y = {0,1,1,2} }            },
	[Z] = {                                                       { .x = {0,2,2,4}, .y = {0,0,1,1} },                   { .x = {2,0,2,0}, .y = {0,1,1,2} },
		    { .x = {0,2,2,4}, .y = {1,1,2,2} },                   { .x = {2,0,2,0}, .y = {0,1,1,2} }
    },
	                                                      [T] = {                                                       { .x = {2,0,2,4}, .y = {0,1,1,1} },                   { .x = {2,2,2,4}, .y = {0,1,2,1} },                   { .x = {0,2,4,2}, .y = {1,1,1,2} },                   { .x = {0,2,2,2}, .y = {1,0,1,2} }            },                                           
};	


void place_InMid(tetro *tet)
{
	for (int i = 0; i < 4; i++) {
		tet->x[i] +=  mid/2 + WIDTH;
	}
	return;
}
void rand_tetro(tetro *tet)
{
	init_rinfo();
	sh = (rand() % 7);
	*tet = tetromino[sh][0];
//	place_InMid(tet);
	return;
}

void rotate_tetro(tetro *tet, int curr_r)
{
	int curr_x, curr_y, mid_x, mid_y;
	mid_x = tetromino[sh][1].x[1];
	mid_y = tetromino[sh][1].y[1];
	curr_x = tet->x[1];
	curr_y = tet->y[1];
	for (int i = 0; i < 4; i++) {
		tet->x[i] = (tetromino[sh][1].x[i] - mid_x) + curr_x;
		tet->y[i] = (tetromino[sh][1].y[i] - mid_y) + curr_y;
	}
	return;
}

void store_tetromino(tetro tet)
{
	for (int i = 0; i < 4; i++) 
		game_board[tet.y[i]][tet.x[i]].block = true;
	return;
}

void update_y(tetro *tet)
{
	for (int i = 0; i < 4; i++)
		tet->y[i]++;
	return;
}

void update_x(tetro *tet, int dir)
{
	for (int i = 0; i < 4; i++)
		tet->x[i] += dir;
	return;
}

bool is_coll(tetro tet)
{
	for (int i = 0; i < 4; i++) 
		if (tet.y[i] >= HEIGHT || tet.x[i] >= WIDTH || game_board[tet.y[i]][tet.x[i]].block)
			return true;
	return false;
}

void blocks_inBoard()
{
	for (int i = 0; i < HEIGHT; i++)
		for (int k = 0; k < WIDTH; k++)
			if(game_board[i][k].block == true)
				mvprintw(i, k, "[]");
	return;
}

bool is_rowTrue(int row)
{  
		for (int i = 0; i < WIDTH; i+=2)
			if (game_board[row][i].block == false)
				return false;
		return true;
}

void update_Boardblock()
{
	int fullrow[20];
	bool need_updation = false;
	for (int y = HEIGHT - 1; y > 0; y--) {
		if (!(is_rowTrue(y))) {
			fullrow[y] = 0;
			continue;
		}else
			need_updation = true;
		fullrow[y] = y;
	}
	if (!need_updation)
		return;
	int tm;
	for (int y = HEIGHT - 1; y > 0; y--) {
		tm = y;
		if (y == fullrow[y])
		//	tm = y - 1;
		for (int x = 0; x < WIDTH; x += 2) {
			second_board[y][x].block = game_board[tm - 1][x].block;
		}
	}
	for (int y = 0; y < HEIGHT; y++)
		for (int x = 0; x < WIDTH; x += 2)
			game_board[y][x].block = second_board[y][x].block;
	return;
}

	
