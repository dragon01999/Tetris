#include<stdio.h>
#include<string.h>
#include<ncurses.h>
#include"render.h"
#include"tetromino.h"

int main(int argc, char *argv[]) {

        block *head;
		head = gen_block(TETRA);
		block *tmp = head;
		for (; tmp!= NULL; tmp = tmp->next) 
			printf("mem: [%p] \n", tmp);
		    
		return 0;
}
