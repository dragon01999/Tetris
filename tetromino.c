#include<stdlib.h>
#include<errno.h>
#include"render.h"
#include"tetromino.h"

block* gen_block(int no_of_blocks)
{
	block *init_block = NULL;
	block *tmp = NULL;
	for (int i = 0; i < no_of_blocks; i++) {
		init_block = malloc(sizeof(block) * TETRA);
		if (!init_block) {
			fprintf(stderr,"Memory allocation failed. Error: %d", errno);
			exit(-1);
		}
		init_block->next = tmp;
		tmp = init_block;
	}


