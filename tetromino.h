#ifndef TETROMINO_H
#define TETROMINO_H

#define TETRA 4
#define TETRA_BLOCK []

typedef struct block
{
	int x;
	int y;
    struct block *next;

}block;

typedef enum tetromino
{
	I = 0,
	O = 1,
	T = 2,
	S = 3,
	Z = 4,
	J = 5,
	L = 6,
} tetromino;

extern tetromino curr_tetromino;

//Assigns random tetromino, not 7-bag system.
void rand_block();

block* gen_block(int no_of_blocks);
/*
void init_tetra(block *initial_block); */

#endif
