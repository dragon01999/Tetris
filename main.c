#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "tetris.h"
#include "render.h"
#include "input.h"
#include "score.h"

#if WITH_SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#endif
int main(int argc, char **argv) {

	#if WITH_SDL
	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		fprintf(stderr, "SDL init failed. SDL Err:%s", SDL_GetError());
		return 1;
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		fprintf(stderr, "SDL Audio device open failed. SDL Err:%s", SDL_GetError());
		return 1;
	}
	Mix_Music *bgm = Mix_LoadMUS("music/tetris-1.mp3");
	if (!bgm) {
		fprintf(stderr, "Failed to open music file. SDL Err:%s", SDL_GetError());
		return 1;
	}
	Mix_PlayMusic(bgm, -1);
    #endif
    init_curses();
    init_ScreenInfo();
    srand(time(NULL));
    tetro tetromino;
    generate_tetromino(&tetromino);
    int highest_score;
    highest_score = 0;
    while (tetris.game_status) {
		print_scores_lvl();
		draw_logo();
		draw_board();
        print_stored_tetromino();
        draw_tetro(tetromino, tetris.curr_piece);
        print_next_tetromino();
		refresh();
		input(&tetromino);
        if (!tetromino_fall(&tetromino)) {
			if (is_game_over(&tetromino))
				tetris.game_status = false;
            store_tetromino(tetromino);
            clear_lines();
            update_scores();
			generate_tetromino(&tetromino);
            print_scores_lvl();
            clean_next();
			clean_tetromino(tetromino, " `");
			refresh();
        }
    }
		clear();
		nodelay(stdscr, FALSE);
		load_score(&highest_score);
		if (tetris.score > highest_score) {
			printw("Congratulations! you have beaten the highest score: %d. Current highest:%d", highest_score, tetris.score);
			store_score(tetris.score);
		} else
		    printw("Highest Score: %d", highest_score);
	getch();
	endwin();
	#if WITH_SDL
	Mix_FreeMusic(bgm);
	Mix_CloseAudio();
	SDL_Quit();
	#endif
	return 0;
}

