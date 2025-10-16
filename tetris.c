#include<stdbool.h>
#include<ncurses.h>
#include<stdlib.h>
#include"render.h"
#include"tetris.h"

bool game_board[height][width];
tetromino sh;
tetris shape[7][4] = {
	[I] = {
    // 0° — horizontal
    { .x = {0, 2, 4, 6}, .y = {1, 1, 1, 1} },

    // 90° — vertical
    { .x = {4, 4, 4, 4}, .y = {0, 1, 2, 3} },

    // 180° — horizontal (flipped but same line)
    { .x = {0, 2, 4, 6}, .y = {2, 2, 2, 2} },

    // 270° — vertical (mirrored back)
    { .x = {2, 2, 2, 2}, .y = {0, 1, 2, 3} }
},	
        [O] = {
		{ .x = {0,2,0,2}, .y = {0,0,1,1} }
        },

        [J] = {
		{ .x = {0,0,2,4}, .y = {0,1,2,2} },
		{ .x = {0,2,2,2}, .y = {0,0,1,2} },
		{ .x = {2,4,2,2}, .y = {0,0,1,2} },
		{ .x = {0,2,4,4}, .y = {1,1,1,2} }
	},
	
	[L] = {
		{ .x = {4,0,2,4}, .y = {0,1,1,1} },
		{ .x = {2,2,2,4}, .y = {0,1,2,2} },
		{ .x = {0,2,4,0}, .y = {1,1,1,2} },
		{ .x = {0,2,2,2}, .y = {0,0,1,2} }
	},
	
	[S] = {
		{ .x = {2,4,0,2}, .y = {0,0,1,1} },
		{ .x = {0,0,2,2}, .y = {0,1,1,2} },
		{ .x = {2,4,0,2}, .y = {1,1,2,2} },
		{ .x = {2,2,4,4}, .y = {0,1,1,2} }
	},

	[Z] = {
		{ .x = {0,2,2,4}, .y = {0,0,1,1} },
		{ .x = {2,0,2,0}, .y = {0,1,1,2} },
		{ .x = {0,2,2,4}, .y = {1,1,2,2} },
		{ .x = {2,0,2,0}, .y = {0,1,1,2} }
	},

	[T] = {
		{ .x = {2,0,2,4}, .y = {0,1,1,1} },
		{ .x = {2,2,2,4}, .y = {0,1,2,1} },
		{ .x = {0,2,4,2}, .y = {1,1,1,2} },
		{ .x = {0,2,2,2}, .y = {1,0,1,2} }
	},
};

void init_tetromino(tetris *arr, int index)
{
        initialize_vars();
        sh = (rand() % 7);
        arr[index] = shape[sh][0];
//        placeIn_Mid(arr);
        return;
}

void rotate_tetris(tetris *tet, int in, int r)
{		
	int rel_x, rel_y, c_x, c_y;
	int m_x = shape[sh][1].x[1];
        int m_y = shape[sh][1].y[1];
	c_x = tet[in].x[1];
	c_y = tet[in].y[1];
	for (int i = 0; i < 4; i++) {
		rel_x = shape[sh][1].x[i] - m_x;
		rel_y = shape[sh][1].y[i] - m_y;
		tet[in].x[i] = rel_x + c_x;
		tet[in].y[i] = rel_y + c_y;
	}
	return;

}


void update_GameBoard(tetris *tet, int in)
{
        for (int i = 0; i < 4; i++) {
        int x = tet[in].x[i];
        int y = tet[in].y[i];
//      if (game_board[y][x] != true)
        game_board[y][x] = true;
        }
        return;
}

void update_y(tetris *tet, int in)
{
	for (int i = 0; i < 4; i++) {
		tet[in].y[i]++;
	}
	return;
}

void update_x(tetris *tet, int in, int dir)
{
    for (int i = 0; i < 4; i++) {
        tet[in].x[i] = tet[in].x[i] + dir;
    }
    return;
}

bool collision(tetris *tet, int in)
{	
	int x, y;
	for (int i = 0; i < 4; i++) {
		x = tet[in].x[i];
		y = tet[in].y[i];
		if (x >= border_x || y >= border_y - 1)
			return true;
		if (game_board[y][x] == true)
			return true;
	}
		return false;
}

void draw_game()
{                                                         for (int i = 0; i < height; i++)                          for (int k = 0; k < width; k++)
            if (game_board[i][k])                                     mvprintw(i, k, "[]");                     return;                                           }



void tetromino_fall(tetris *tet, int in)
{
	bool coll = false;
	tetris tmp[2];
    tmp[0] = tet[in];
	while (!coll) {
		input(tmp, 0);
		update_y(tmp, 0);
		if (collision(tmp, 0) == true)
			coll = true;
		if(coll == false)
		  tet[in] = tmp[0];
		draw_tetromino(tet, in);
		draw_board();
		draw_game();
		refresh();
		napms(400);
	//	input(tet, in);
		clear();

	}
	update_GameBoard(tet, in);
	return;
}
					

