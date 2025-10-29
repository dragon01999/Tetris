#include <ncurses.h>
#include "render.h"

int MAX_X, MAX_Y;
int left_x, right_x;

void init_curses()
{
	initscr();
    cbreak();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
	curs_set(0);
	noecho();
	if (has_colors()) {
		start_color();
		use_default_colors();
		init_pair(I + 1, 51, -1);
		init_pair(O + 1, 220, -1);
		init_pair(J + 1, 21, -1);
		init_pair(L + 1, 214, -1);
		init_pair(S + 1, 46, -1);
		init_pair(Z + 1, 196, -1);
		init_pair(T + 1, 201, -1);
		init_pair(BOARD_COLOR, COLOR_GREEN, -1);
	}
}
void init_BoardInfo()
{
	getmaxyx(stdscr, MAX_Y, MAX_X);
	left_x = (MAX_X - BOARD_WIDTH) / 2;
	right_x = left_x + BOARD_WIDTH;

}

void draw_hor(int x, int y, int times, char *obj, int obj_len)
{
	for (int i = 0; i < times; i += obj_len) 
		mvprintw(y, x + i, "%s", obj);
	
}

void draw_ver(int x, int y, int times, char *obj)
{
	for (int i = 0; i < times; i++)
		mvprintw(y + i, x, "%s", obj);
}

void draw_board()
{
	attron(COLOR_PAIR(BOARD_COLOR));
	for (int i = 0; i < BOARD_HEIGHT; i++)
		draw_hor(left_x, i, BOARD_WIDTH + 1, "`", 1);
	draw_hor(left_x, BOARD_HEIGHT, BOARD_WIDTH + 1, "=", 1);
	draw_hor(left_x, BOARD_HEIGHT + 1, BOARD_WIDTH, "\\/", 2);
	draw_ver(left_x - 1, 0, BOARD_HEIGHT + 1, "<!");
	draw_ver(left_x + BOARD_WIDTH + 1, 0, BOARD_HEIGHT + 1, "!>");
	attroff(COLOR_PAIR(BOARD_COLOR));
}

void draw_tetro(tetro tet, int piece)
{
	attron(COLOR_PAIR(piece + 1));
	for (int i = 0; i < 4; i++) {
		mvprintw(tet.y[i], tet.x[i], "[]");
	}
	attroff(COLOR_PAIR(piece + 1));
	return;
}

void clean_tetromino(tetro tet, char *str)
{
	attron(COLOR_PAIR(BOARD_COLOR));
	for (int i = 0; i < 4; i++) 
		mvprintw(tet.y[i], tet.x[i], "%s",str);	
	attroff(COLOR_PAIR(BOARD_COLOR));
	return;
}

/* converts X coordinates from X*2 to X/2 */
void screen_to_logic(tetro *tet)
{
        for (int i = 0; i < 4; i++)
                tet->x[i] = (tet->x[i] - left_x) / 2;
        return;
}

/* Converts actual X to X * 2 */
void logic_to_screen(tetro *tet) {
    for (int i = 0; i < 4; i++) {
        tet->x[i] += left_x + 1;
    }
}

/* Places the spawned piece in the middle */
void place_in_mid(tetro *tet) {
    for (int i = 0; i < 4; i++) {
        tet->x[i] += BOARD_WIDTH / 2 - 4;

        /* the y is being offset by 1 so that when a tetromino spawns,
           it appears to be coming from above the ceiling */
        tet->y[i] -= 1;
    }
}
