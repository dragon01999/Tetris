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

bool collision(tetris *arr, int i, int n)
{
	for (int k = 0; k < 4; k++) {
		if (arr[i].y[k] == border_y - 2)
			return true;
	}
	for (int k = 0; k < n; k++) {
		for (int j = 0; j < 4; j++) {
			if (k != i && arr[i].y[j] == arr[k].y[j])
				return true;
		}
	}
	return false;
}


void update_y(tetris *arr, int pos)
{   
	placeIn_Mid(arr, pos);
	while (!collision(arr, 0, 1)) {
        clear();
		arr[pos].y[3] = arr[pos].y[3] + 1;
		arr[pos].y[2] = arr[pos].y[2] + 1;
		arr[pos].y[1] = arr[pos].y[1] + 1;
		arr[pos].y[0] = arr[pos].y[0] + 1;
		draw_tetromino(arr);
		draw_board();
        refresh();
		napms(800);
	}
	getch();
	return;
}



