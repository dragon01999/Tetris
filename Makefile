CC = gcc
CFLAGS = -Wall -O2 -g -DWITH_SDL
LDFLAGS = -lncurses

OBJ = tetris.o render.o input.o score.o main.o

all: game

game: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o game $(LDFLAGS)
	rm -f $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean

clean:
	rm -f $(OBJ) game
