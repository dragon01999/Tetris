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
int next = -1, curr_piece, curr_rot;
static int cleared_lines, total_cleared_lines;
tetro next_tetro;
/* X coordinates are stored as X*2 or X+1 since each tetromino block is printed as [] */
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

/* converts X coordinates from X*2 to X/2 */
void screen_to_logic(tetro *tet)
{
	for (int i = 0; i < 4; i++)
		tet->x[i] = (tet->x[i] - left_x) / 2;
	return;
}

/* converts actual X to X*2 */
void logic_to_screen(tetro *tet)
{
	for (int i = 0; i < 4; i++)
		tet->x[i] += left_x + 1;
	return;
}

/* Places the spawned piece in middle */
void place_InMid(tetro *tet)
{
	for (int i = 0; i < 4; i++) {
		tet->x[i] +=  BOARD_WIDTH/2 - 4;
/* the y is being offsetted by 2 so that when a tetromino spawns it appears to be coming from above ceiling */
		tet->y[i] -= 2;
	}
	return;
}

/* spawns new piece */
void generate_tetromino(tetro *tet)
{
	init_BoardInfo();
	if (next == -1) {
		curr_piece = (rand() % 7);
		next = (rand() % 7);
	}
	curr_piece = next;
	next = (rand() % 7);

	*tet = tetromino[curr_piece][0];
	curr_rot = 0;
	logic_to_screen(tet);
    place_InMid(tet);
	return;
}

/* rotates pieces */
void rotate_tetromino(tetro *tet, int curr_r)
{
	int curr_x, curr_y, mid_x, mid_y;
	mid_x = tetromino[curr_piece][curr_rot].x[1];
	mid_y = tetromino[curr_piece][curr_rot].y[1];
	curr_x = tet->x[1];
	curr_y = tet->y[1];
	for (int i = 0; i < 4; i++) {
		tet->x[i] = (tetromino[curr_piece][curr_rot].x[i] - mid_x) + curr_x;
		tet->y[i] = (tetromino[curr_piece][curr_rot].y[i] - mid_y) + curr_y;
	}
	return;
}

/* stores pieces in game_board */
void store_tetromino(tetro tet)
{
	/* convert X*2 to X/2 before storing */
	screen_to_logic(&tet);
	for (int i = 0; i < 4; i++) { 
		game_board[tet.y[i]][tet.x[i]].block = true;
		game_board[tet.y[i]][tet.x[i]].color = curr_piece;
	}
	return;
}

/* update y for passed piece */
void update_y(tetro *tet)
{
	for (int i = 0; i < 4; i++)
		tet->y[i]++;
	return;
}

/* update x for passed piece by dir which can be negative or positive */
void update_x(tetro *tet, int dir)
{
	for (int i = 0; i < 4; i++)
		tet->x[i] += dir;
	return;
}

/* check for collisions. The branching is based on priorities */
int is_coll(tetro tet)
{
	tetro tmp = tet;
	screen_to_logic(&tmp);
	for (int i = 0; i < 4; i++) {
		if (game_board[tmp.y[i]][tmp.x[i]].block || tet.y[i] >= HEIGHT)
			return 1;
		if (tet.x[i] > right_x || tet.x[i] < left_x + 1) 
			return 2;
	}
	return 0;
}

/* make the piece fall by 1. returns false to indicate
 no collision has occured so spawn is not required */
bool tetromino_fall(tetro *tet)
{
	tetro tmp = *tet;
	update_y(&tmp);
	if (is_coll(tmp)) 
		return false;
	*tet = tmp;
	return true;
}

/* print stored pieces or remnant blocks inside the game_board */
void print_stored_tetromino()
{
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			if(game_board[y][x].block == true) {
				attron(COLOR_PAIR(game_board[y][x].color));
				/* X*2 since each block is []. offset by left wall X+1 */
				mvprintw(y, x * 2 + left_x + 1, "[]");                attroff(COLOR_PAIR(game_board[y][x].color));	

			}
		}
	}
	return;
}

void print_next_tetromino()
{
	next_tetro = tetromino[next][0];
	int x = left_x / 2 - 4;
	int y = BOARD_HEIGHT / 2;
	for (int i = 0; i < 4; i++) {
		next_tetro.x[i] += x;
		next_tetro.y[i] += y;
	}
	draw_tetro(next_tetro, next);
	return;
}

void clean_next()
{
	clean_tetromino(next_tetro, "  ");
	return;
}

/* Check if the row or the line is full for a given Y */
bool is_row_full(int row)
{  
		for (int i = 0; i < WIDTH; i++)
			if (game_board[row][i].block == false)
				return false;
		return true;
}

/* Deletes the full rows */
void clear_row()
{   
	cleared_lines = 0;
	int non_fullrow[20];
	bool need_updation = false;
	for (int i = HEIGHT - 1; i > 0; i--) {
		if (!is_row_full(i)) {
/* Store row numbers which are not full */
			non_fullrow[i] = i;
			continue;
		}
/* for every full row increment cleared_lines */
		cleared_lines++; 
		need_updation = true;
	}
	if (!need_updation)
		return;
	int y = HEIGHT - 1;
	int s_y = HEIGHT - 1;
	while (y != 0) {

		/* make sure the row numbers stored in non_full rows arent out if bounds */
		if (non_fullrow[y] > 0 && non_fullrow[y] < 20) {
		/* copy all non full rows to tmp board */
		memcpy(tmp_board[s_y], game_board[y], sizeof(table) * WIDTH);
		s_y--;
	}
		y--;
	}
	    /* write back the nonfull rows from tmp board to game_board */
	for (int y = HEIGHT - 1; y > 0; y--) {
		memcpy(game_board[y], tmp_board[y], sizeof(table) * WIDTH);
	}
	/* update total cleared lines. */
	total_cleared_lines += cleared_lines;
	return;
}

		
