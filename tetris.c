#include<time.h>
#include<ncurses.h>
#include"render.h"
#include"tetris.h"


tetris shape[7] = {
	[0] = {
		.x = {0, 0, 0, 0},
		.y = {0, 1, 2, 3}
	},
	[1] = {
		.x = {0, 2, 4, 6},
		.y = {0, 0, 0, 0}
	},
};


void init_tetromino(tetris *arr, int index, tetromino s)
{   
	initialize_vars();
	arr[index] = shape[s];
	placeIn_Mid(arr);
	return;
}

void placeIn_Mid(tetris *arr)
{
	for (int i = 0; i < 4; i++) {
		arr[0].x[i] = mid;
		printf("%i", mid);
	}
	return;
}

void update_y(tetris *arr)
{   
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



