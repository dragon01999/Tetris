#include<time.h>
#include<ncurses.h>
#include<stdlib.h>
#include"render.h"
#include"tetris.h"

bool game_board[height][width];
tetris shape[7] = {
	[I] = {
		.x = {0, 0, 0, 0},
		.y = {0, 1, 2, 3}
	},
	[O] = {
		.x = {0, 2, 0, 2},
		.y = {0, 0, 1, 1}
	},
	[T] = {
		.x = {0, 2, 4, 2},
		.y = {0, 0, 0, 1}
	},
	[S] = {
		.x = {0, 2, 2, 4},
		.y = {0, 0, 1, 1}	
	},
	[Z] = {
		.x = {2, 4, 0, 2},
	    .y = {0, 0, 1, 1}		
	},
	[J] = {
		.x = {2, 2, 2, 0},
		.y = {0, 1, 2, 2}
	},
	[L] = {
		.x = {2, 2, 2, 0},
		.y = {0, 1, 2, 2}
	},
};


void init_tetromino(tetris *arr, int index)
{   
	initialize_vars();
	tetromino sh = (rand() % 7);
	arr[index] = shape[sh];
//	placeIn_Mid(arr);
	return;
}

void placeIn_Mid(tetris *arr, int pos)
{
	fprintf(stderr, "  arr0x3: %i ", arr[0].x[3]);
	int mid_arr = arr[pos].x[2];
	arr[pos].x[0] = (arr[pos].x[2] + mid - 1) - arr[0].x[0]; 
	arr[pos].x[1] = (arr[pos].x[2] + mid - 1) - arr[0].x[1];
	arr[pos].x[2] = (arr[pos].x[2] + mid - 1) - arr[pos].x[2];
	arr[pos].x[3] = (mid_arr + mid - 1) - arr[pos].x[3];

	fprintf(stderr, "  arr0x3: %i mid: %i",  arr[pos].x[3], mid);
}

void update_GameBoard(tetris *tet, int in)
{
	for (int i = 0; i < 4; i++) {
        int x = tet[in].x[i];
        int y = tet[in].y[i];
		if (game_board[y][x] != true)
		game_board[y][x] = true;
	}
	return;
}

bool collision(tetris *tet, int in)
{
	for (int i = 0; i < 4; i++) {
		int x = tet[in].x[i];
		int y = tet[in].y[i];
		if (game_board[y][x] == true)
			return true;
		if (y == border_y - 2 || x == border_x)
			return true;
	}
	return false;
}

void tetromino_fall(tetris *tet, int in)
{   
	bool coll = false;
	while (!coll) {
		for (int i = 0; i < 4; i++) {
			tet[in].y[i] += 1;
			if (collision(tet, in)) {
				coll = true;
				break;
			}
		}
			

		draw_tetromino(tet, in);
		refresh();
		napms(400);
		clear();
	}
	update_GameBoard(tet, in);
	return;
}

void draw_game()
{                                                         for (int i = 0; i < height; i++)                          for (int k = 0; k < width; k++)
            if (game_board[i][k])                                     mvprintw(i, k, "[]");                     return;                                           }
