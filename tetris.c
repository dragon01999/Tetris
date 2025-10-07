#include<time.h>
#include<ncurses.h>
#include"render.h"
#include"tetris.h"


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
		.x = {2, 4, 0, 2},
		.y = {0, 0, 1, 1}
	},
	[Z] = {
		.x = {0, 2, 2, 4},
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

void placeIn_Mid(tetris *arr)
{
	fprintf(stderr, "  arr0x3: %i ", arr[0].x[3]);
	int mid_arr = arr[0].x[2];
	arr[0].x[0] = (arr[0].x[2] + mid - 1) - arr[0].x[0]; 
	arr[0].x[1] = (arr[0].x[2] + mid - 1) - arr[0].x[1];
	arr[0].x[2] = (arr[0].x[2] + mid - 1) - arr[0].x[2];
	arr[0].x[3] = (mid_arr + mid - 1) - arr[0].x[3];

	fprintf(stderr, "  arr0x3: %i mid: %i",  arr[0].x[3], mid);
}

void update_y(tetris *arr)
{   
	placeIn_Mid(arr);
	while (arr[0].y[3] != border_y - 2) {
        clear();
		arr[0].y[3] = arr[0].y[3] + 1;
		arr[0].y[2] = arr[0].y[2] + 1;
		arr[0].y[1] = arr[0].y[1] + 1;
		arr[0].y[0] = arr[0].y[0] + 1;
		draw_tetromino(arr);
		draw_board();
        refresh();
		napms(800);
	}
	getch();
	return;
}



