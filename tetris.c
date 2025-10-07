#include<time.h>
#include<ncurses.h>
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


void init_tetromino(tetris *arr, int index, tetromino s)
{   
	initialize_vars();
	arr[index] = shape[s];
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

bool collision(tetris *tet, int in)
{
	for (int i = 0; i < 4; i++) {
		if (tet[in].y[i] == border_y - 2 || tet[in].x[i] == border_x)
			return true;
		int x = tet[in].x[i];
		int y = tet[in].y[i];
		if (game_board[y][x] == true)
			return true;
	}
	return false;
}

void update(char dir, tetris *tet, int in)
{
	if (dir == 'y') {
		for (int i = 0; i < 4; i++)
			tet[in].y[i] += 1;
		return;
	}
	else if (dir == 'x') {
		for (int i = 0; i < 4; i++)                               tet[in].x[i] += 1;                                return;
	}
	return;
}
