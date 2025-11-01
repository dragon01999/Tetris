CC = gcc
SDL_CFLAGS := $(shell pkg-config --cflags sdl2 SDL2_mixer 2>/dev/null)
SDL_LIBS := $(shell pkg-config --libs sdl2 SDL2_mixer 2>/dev/null)

ifeq ($(SDL_CFLAGS),)
	WITH_SDL = 0
else
	WITH_SDL = 1
endif

CFLAGS = -Wall -O2 -g
LDFLAGS = -lncurses

ifeq ($(WITH_SDL), 1)
	CFLAGS += -DWITH_SDL $(SDL_CFLAGS)
	LDFLAGS += $(SDL_LIBS)
endif

OBJ = tetris.o render.o input.o score.o main.o

all: game

game: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o game $(LDFLAGS)
	rm -f $(OBJ)
	@clear

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean

clean:
	rm -f $(OBJ) game
