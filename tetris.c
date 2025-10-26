#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ncurses.h>
#include "tetris.h"
#include "render.h"

//actual game board which will track stored tetrominos
table game_board[HEIGHT][WIDTH];
//tmp board 
table tmp_board[HEIGHT][WIDTH];
int sh, curr_rot; 
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
	[J] = {                                                       { .x = {0,0,2,4}, .y = {0,1,1,1} },                   { .x = {0,2,2,2}, .y = {0,0,1,2} },                   { .x = {2,4,2,2}, .y = {0,0,1,2} },                   { .x = {0,2,4,4}, .y = {1,1,1,2} }            },                                                                                                          [L] = {                                                       { .x = {0,0,2,4}, .y = {0,1,1,1} },                   { .x = {2,2,2,4}, .y = {0,1,2,2} },                   { .x = {0,2,4,0}, .y = {1,1,1,2} },                   { .x = {0,2,2,2}, .y = {0,0,1,2} }            },                                                                                                          [S] = {                                                       { .x = {2,4,0,2}, .y = {0,0,1,1} },
		    { .x = {0,0,2,2}, .y = {0,1,1,2} },
	        { .x = {2,4,0,2}, .y = {1,1,2,2} },                   { .x = {2,2,4,4}, .y = {0,1,1,2} }            },
	[Z] = {                                                       { .x = {0,2,2,4}, .y = {0,0,1,1} },                   { .x = {2,0,2,0}, .y = {0,1,1,2} },
		    { .x = {0,2,2,4}, .y = {1,1,2,2} },                   { .x = {2,0,2,0}, .y = {0,1,1,2} }
    },
	                                                      [T] = {                                                       { .x = {2,0,2,4}, .y = {0,1,1,1} },                   { .x = {2,2,2,4}, .y = {0,1,2,1} },                   { .x = {0,2,4,2}, .y = {1,1,1,2} },                   { .x = {0,2,2,2}, .y = {1,0,1,2} }            },                                           
};	

void screen_to_logic(tetro *tet)
{
	for (int i = 0; i < 4; i++)
		tet->x[i] = (tet->x[i] - left_x) / 2;
	return;
}

void logic_to_screen(tetro *tet)
{
	for (int i = 0; i < 4; i++)
		tet->x[i] += left_x + 1;
	return;
}

void place_InMid(tetro *tet)
{
	for (int i = 0; i < 4; i++) {
		tet->x[i] +=  BOARD_WIDTH/2 - 4;
	}
	return;
}
void generate_tetromino(tetro *tet)
{
	init_BoardInfo();
	sh = (rand() % 7);
	*tet = tetromino[sh][0];
	curr_rot = 0;
	logic_to_screen(tet);
    place_InMid(tet);
	return;
}

void rotate_tetromino(tetro *tet, int curr_r)
{
	int curr_x, curr_y, mid_x, mid_y;
	mid_x = tetromino[sh][curr_rot].x[1];
	mid_y = tetromino[sh][curr_rot].y[1];
	curr_x = tet->x[1];
	curr_y = tet->y[1];
	for (int i = 0; i < 4; i++) {
		tet->x[i] = (tetromino[sh][curr_rot].x[i] - mid_x) + curr_x;
		tet->y[i] = (tetromino[sh][curr_rot].y[i] - mid_y) + curr_y;
	}
	return;
}

void store_tetromino(tetro tet)
{
	screen_to_logic(&tet);
	for (int i = 0; i < 4; i++) { 
		game_board[tet.y[i]][tet.x[i]].block = true;
		game_board[tet.y[i]][tet.x[i]].color = sh;
	}
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
	tetro tmp = tet;
	screen_to_logic(&tmp);
	for (int i = 0; i < 4; i++) {
		if (game_board[tmp.y[i]][tmp.x[i]].block || tet.y[i] >= HEIGHT)
			return true;
		if (tet.x[i] > right_x || tet.x[i] < left_x + 1) 
			return true;
	}
	return false;
}

void tetromino_fall(tetro *tet, float ms)
{
	tetro tmp = *tet;
	update_y(&tmp);
	if (!is_coll(tmp)) {
		*tet = tmp;
		draw_tetro(*tet);
		refresh();
		napms(ms);
	}
	return;
}

void print_stored_tetromino()
{
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			if(game_board[y][x].block == true) {
				attron(COLOR_PAIR(game_board[y][x].color));
				mvprintw(y, x * 2 + left_x + 1, "[]");                attroff(COLOR_PAIR(game_board[y][x].color));	

			}
		}
	}
	return;
}

bool is_row_full(int row)
{  
		for (int i = 0; i < WIDTH; i++)
			if (game_board[row][i].block == false)
				return false;
		return true;
}

void clear_row()
{
	int non_fullrow[20];
	bool need_updation = false;
	for (int i = HEIGHT - 1; i > 0; i--) {
		if (!is_row_full(i)) { 
			non_fullrow[i] = i;
			continue;
		}
		need_updation = true;
	}
	if (!need_updation)
		return;
	int y = HEIGHT - 1;
	int s_y = HEIGHT - 1;
	while (y != 0) {
		if (non_fullrow[y] > 0 && non_fullrow[y] < 20) {
		memcpy(tmp_board[s_y], game_board[y], sizeof(table) * WIDTH);
		s_y--;
	}
		y--;
	}
	for (int y = HEIGHT - 1; y > 0; y--) {
		memcpy(game_board[y], tmp_board[y], sizeof(table) * WIDTH);
	}
	return;
}

		
