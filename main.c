#include <stdio.h>
#include <ncurses.h>
#include "render.h"

int main(int argc, char **argv) {
	initscr();
	cbreak();
	init_rinfo();
	for (int i = 0; i < 20; i++) {

	endwin();
	return 0;
}

