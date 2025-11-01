#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ncurses.h>
#include "tetris.h"
#include "render.h"

/* game board to track stored tetrominos */
table game_board[HEIGHT][WIDTH];
table tmp_board[HEIGHT][WIDTH];
struct GameState tetris = {
	.game_status = true,
	.next = -1,
	.rotation = 0,
	.total_cleared = 0,
	.score = 0,
	.level = 1,
};


/* X coordinates are stored as X*2 since each tetromino block is printed as [] */
const tetro tetromino[7][4] = {
	[I] = { 
		    { .x = {0,2,4,6}, .y = {1,1,1,1} },
		    { .x = {4,4,4,4}, .y = {0,1,2,3} },
		    { .x = {0,2,4,6}, .y = {2,2,2,2} },
	 	    { .x = {2,2,2,2}, .y = {0,1,2,3} }
	},
	[O] = {
		    { .x = {0,2,0,2}, .y = {0,0,1,1} }
	},
	[J] = { 
		    { .x = {0,0,2,4}, .y = {0,1,1,1} },  
		    { .x = {0,2,2,2}, .y = {0,0,1,2} },     
		    { .x = {2,4,2,2}, .y = {0,0,1,2} },      
  		    { .x = {0,2,4,4}, .y = {1,1,1,2} }   
	},                                               
	[L] = { 
		    { .x = {0,0,2,4}, .y = {0,1,1,1} },     
  	       	{ .x = {2,2,2,4}, .y = {0,1,2,2} },     
      		{ .x = {0,2,4,0}, .y = {1,1,1,2} }, 
		    { .x = {0,2,2,2}, .y = {0,0,1,2} }      
  	},                                                 	 
    [S] = { 
		    { .x = {2,4,0,2}, .y = {0,0,1,1} },
		    { .x = {0,0,2,2}, .y = {0,1,1,2} },
	        { .x = {2,4,0,2}, .y = {1,1,2,2} }, 
     		{ .x = {2,2,4,4}, .y = {0,1,1,2} }       
   	},
	[Z] = {
		    { .x = {0,2,2,4}, .y = {0,0,1,1} },    
 		    { .x = {2,0,2,0}, .y = {0,1,1,2} },
		    { .x = {0,2,2,4}, .y = {1,1,2,2} },   
    		{ .x = {2,0,2,0}, .y = {0,1,1,2} }
    },
	[T] = {     
		    { .x = {2,0,2,4}, .y = {0,1,1,1} },				
	  	    { .x = {2,2,2,4}, .y = {0,1,2,1} },   
		    { .x = {0,2,4,2}, .y = {1,1,1,2} },     
		    { .x = {0,2,2,2}, .y = {1,0,1,2} }      
    },                                           
};	

/* spawns new piece */
void generate_tetromino(tetro *tet)
{
	if (tetris.next == -1) {
		tetris.curr_piece = (rand() % 7);
		tetris.next = (rand() % 7);
	} 
	tetris.curr_piece = tetris.next;
	tetris.next = (rand() % 7);
	*tet = tetromino[tetris.curr_piece][0];
	tetris.rotation = 0;
	logic_to_screen(tet);
    place_in_mid(tet);
	return;
}

/* rotates tetromino using precomputed rotation states */
int rotate_tetromino(tetro *tet)
{
	int curr_x, curr_y, mid_x, mid_y;
	/* store next rotation pivot. 1 is taken as mid */
	mid_x = tetromino[tetris.curr_piece][tetris.rotation].x[1];
	mid_y = tetromino[tetris.curr_piece][tetris.rotation].y[1];
	/* stores current piece pivots */
	curr_x = tet->x[1];
	curr_y = tet->y[1];
	for (int i = 0; i < 4; i++) {
		tet->x[i] = (tetromino[tetris.curr_piece][tetris.rotation].x[i] - mid_x) + curr_x;
		tet->y[i] = (tetromino[tetris.curr_piece][tetris.rotation].y[i] - mid_y) + curr_y;
	}
	return 0;
}

/* stores pieces in game_board */
void store_tetromino(tetro tet)
{
	/* convert X*2 to X/2 before storing */
	screen_to_logic(&tet);
	for (int i = 0; i < 4; i++) {
	/* To prevent writing X in next rows memory address in case X logical coordinates exceeds 9 */
		if (tet.x[i] >= 0 && tet.x[i] < WIDTH) {
			game_board[tet.y[i]][tet.x[i]].block = true;
	/* +1 since enum of pieces starts from 0 and for colorpair it starts from 1 */
			game_board[tet.y[i]][tet.x[i]].color = tetris.curr_piece + 1;
		}
	}
	return;
}

/* update y for passed piece */
void move_down(tetro *tet)
{
	for (int i = 0; i < 4; i++)
		tet->y[i]++;
	return;
}

/* Hard drop */
void hard_drop(tetro *tet)
{
	tetro tmp = *tet;
	while (!is_colliding(tmp) && !is_overlapping(&tmp)) {
		*tet = tmp;
		move_down(&tmp);
	}
	return;
}

/* update x for passed piece by dir which can be negative or positive */
void move_direction(tetro *tet, int dir)
{
	for (int i = 0; i < 4; i++)
		tet->x[i] += dir;
	return;
}

/* check for wall collisions */
bool is_colliding(tetro tet)
{
	for (int i = 0; i < 4; i++) 
		if (tet.x[i] > screen.right_wall || tet.x[i] < screen.left_wall + 1) 
			return true;
	return false;
}

/* check if piece is overlapping or hit the bottom */
bool is_overlapping(tetro *tet)
{
	tetro tmp = *tet;
	screen_to_logic(&tmp);
	for (int i = 0; i < 4; i++) 
		if (tet->y[i] >= BOARD_HEIGHT || game_board[tmp.y[i]][tmp.x[i]].block == true)
			return true;
	return false;
}

/* check if any block's Y inside a piece is hitting the ceiling and at the same time overlapping */
bool is_game_over(tetro *tet)
{
	for (int i = 0; i < 4; i++) 
		if (tet->y[i] <= 0 && is_overlapping(tet))
			return true;
	return false;
}

/* make the piece fall by 1. returns true to indicate
 no collision has occured so spawn is not required */
bool tetromino_fall(tetro *tet)
{
	tetro tmp = *tet;
	move_down(&tmp);
	if (is_overlapping(&tmp)) {
		return false;
	}
	*tet = tmp;
	return true;
}

/* Check if the row or the line is full for a given Y */
bool is_lineFull(int line)
{  
		for (int i = 0; i < WIDTH; i++)
			if (game_board[line][i].block == false)
				return false;
		return true;
}

/* Deletes the full rows */
void clear_lines(void)
{   
	tetris.cleared_lines = 0;
	int non_fullrow[20];
	memset(non_fullrow, 0, sizeof(non_fullrow));
	bool need_updation = false;
	for (int i = HEIGHT - 1; i > 0; i--) {
		if (!is_lineFull(i)) {
        /* Store row numbers which are not full */
			non_fullrow[i] = i;
			continue;
		}
        /* for every full row increment cleared_lines */
		tetris.cleared_lines++; 
		need_updation = true;
	}
	if (!need_updation)
		return;
	int y = HEIGHT - 1;
	int tmp_y = HEIGHT - 1;
	while (y >= 0) {
		/* make sure the row numbers stored in non_full rows arent out if bounds */
		if (non_fullrow[y] > 0 && non_fullrow[y] < 20) {
		/* copy all non full rows to tmp board */
		memcpy(tmp_board[tmp_y], game_board[y], sizeof(table) * WIDTH);
		tmp_y--;
	}
		y--;
	}
	    /* write back the nonfull rows from tmp board to game_board */
	memcpy(game_board, tmp_board, sizeof(game_board));
	    /* update total cleared lines. */
	tetris.total_cleared += tetris.cleared_lines;
	return;
}

