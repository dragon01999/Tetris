#ifndef TETROMINO_H
#define TETROMINO_H

#define block_size 4
#define tetra_block []

typedef struct block
{
	int x;
	int y;
	block *next;

}block;

typedef enum tetromino
{
	I = 0,
	O = 1,
	T = 2,
	S = 3,
	Z = 4,
	J = 5,
	I = 6,
};

tetromino curr_tetra;

void rand_block();

block* gen_block(block *initial_block);

void init_tetra(block *initial_block);

#endif
