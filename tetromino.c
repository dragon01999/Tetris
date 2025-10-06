#include<time.h>
#include<stdlib.h>
#include<errno.h>
#include"render.h"
#include"tetromino.h"

typedef struct {
	int x[4];
	int y[4];
} TetrominoShapeData;

tetromino curr_tetromino;

static const TetrominoShapeData shape_data[7] = {
	//[0] is I
	[0] = {
		.x = {0, 0, 0, 0},
		.y = {0, 1, 2, 3}
	},
	//[1] is O
	[1] = {
		.x = {0, 1, 0, 0},
		.y = {0, 1, 0, 0}
	},
};



block* gen_block(int no_of_block)
{
	block *init_block = NULL;
	block *tmp = NULL;
	for (int i = 0; i < no_of_block; i++) {
		init_block = malloc(sizeof(block));
		if (!init_block) {
			fprintf(stderr,"Memory allocation failed. Error: %d", errno);
			exit(-1);
		}
		init_block->next = tmp;
		tmp = init_block;
	}
	return init_block;
}

void rand_block()
{
	srand(time(NULL));
	curr_tetromino = (rand() % 7);// capping it to 7
    return;
}
			
