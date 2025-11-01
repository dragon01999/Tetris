#include <ncurses.h>
#include "render.h"

static void draw_hor(int x, int y, int times, char *obj, int obj_len);                                      

static void draw_ver(int x, int y, int times, char *obj);

int MAX_Y, MAX_X;
struct ScreenInfo screen;

void init_curses(void)
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
void init_ScreenInfo(void)
{
	getmaxyx(stdscr, MAX_Y, MAX_X);
	screen.left_wall = (MAX_X - BOARD_WIDTH) / 2;
	screen.right_wall = screen.left_wall + BOARD_WIDTH;
	/* offsetting by 1 so it will be at exact center */
    screen.left_wall -= 1;
	screen.right_wall -= 1;

}

static void draw_hor(int x, int y, int times, char *obj, int obj_len)
{
	for (int i = 0; i < times; i += obj_len) 
		mvprintw(y, x + i, "%s", obj);
	return;
	
}

static void draw_ver(int x, int y, int times, char *obj)
{
	for (int i = 0; i < times; i++)
		mvprintw(y + i, x, "%s", obj);
	return;
}

void draw_logo(void)
{
	int x = screen.left_wall;
	int y = (BOARD_HEIGHT - 2) / 2;
	attron(COLOR_PAIR(BOARD_COLOR));
	/* y has offsets to make sure it doesn't get overwriten by next piece screen */
	mvprintw(y + 6, x - 11, "[]");
	mvprintw(y + 7, x - 11, "TETRIS");
    mvprintw(y + 8, x - 7, "[]");
	attroff(COLOR_PAIR(BOARD_COLOR));
    return;
}

void draw_board(void)
{
	attron(COLOR_PAIR(BOARD_COLOR));
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		draw_hor(screen.left_wall, i, BOARD_WIDTH + 1, "` ", 2);
	}
	draw_hor(screen.left_wall, BOARD_HEIGHT, BOARD_WIDTH + 1, "=", 1);
	draw_hor(screen.left_wall + 1, BOARD_HEIGHT + 1, BOARD_WIDTH, "\\/", 2);
	draw_ver(screen.left_wall - 1, 0, BOARD_HEIGHT + 1, "<!");
	draw_ver(screen.left_wall + BOARD_WIDTH + 1, 0, BOARD_HEIGHT + 1, "!>");
	attroff(COLOR_PAIR(BOARD_COLOR));
	return;
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
	for (int i = 0; i < 4; i++) {
		mvprintw(tet.y[i], tet.x[i], "%s",str);	
	}
	attroff(COLOR_PAIR(BOARD_COLOR));
	return;
}

/* Prints the next tetromino on the left side of the screen */
void print_next_tetromino(void)
{
    tetris.next_tetromino = tetromino[tetris.next][0];
    int x = screen.left_wall - 10;
    int y = BOARD_HEIGHT / 2;

    for (int i = 0; i < 4; i++) {
        tetris.next_tetromino.x[i] += x;
        tetris.next_tetromino.y[i] += y;
    }
    attron(COLOR_PAIR(BOARD_COLOR));
    draw_hor(x - 1, y - 2, 8, "_", 1);
    draw_hor(x - 1, y + 2, 8, "_", 1);
    mvprintw(y - 3, x, "Next:");
    attroff(COLOR_PAIR(BOARD_COLOR));
    draw_tetro(tetris.next_tetromino, tetris.next);
    return;
}

/* Cleans the previous preview of next tetromino */
void clean_next(void)
{
    clean_tetromino(tetris.next_tetromino, "  ");
    return;
}

/* Prints all stored pieces (remnant blocks) inside the game_board */
void print_stored_tetromino(void)
{
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (game_board[y][x].block == true) {
                attron(COLOR_PAIR(game_board[y][x].color));
                /* x * 2 since each block is "[]", offset by left wall */
                mvprintw(y, x * 2 + screen.left_wall + 1, "[]");
                attroff(COLOR_PAIR(game_board[y][x].color));
            }
        }
    }

    return;
}

/* converts X coordinates from X*2 to X/2 */
void screen_to_logic(tetro *tet)
{
        for (int i = 0; i < 4; i++) {
                tet->x[i] = (tet->x[i] - screen.left_wall) / 2;
	}
        return;
}

/* Converts actual X to X * 2 */
void logic_to_screen(tetro *tet) {
    for (int i = 0; i < 4; i++) {
        tet->x[i] += screen.left_wall + 1;
    }
    return;
}

/* Places the spawned piece in the middle */
void place_in_mid(tetro *tet) {
    int offset = 4;
    if (tetris.curr_piece == O)
	    offset = 2;
    for (int i = 0; i < 4; i++) {
        tet->x[i] += BOARD_WIDTH / 2 - offset;
        /* the y is being offset by 1 so that when a tetromino spawns,
           it appears to be coming from above the ceiling */
        tet->y[i] -= 1;
    }
    return;
}
