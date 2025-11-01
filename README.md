# Terminal Tetris

A ncurses based Tetris clone written in C. Optional SDL music bgm included if SDL2 & SDL2_mixer are available.

## Controls
-> ← / →: Move left/right  
-> ↑: Rotate  
-> ↓: Soft drop  
-> Space: Hard drop  
-> P: Pause  
-> Q: Quit

## Dependencies
This game optionally supports music playback using SDL2 and SDL2_mixer. If these libraries are not installed, the game will build and run in silent mode.

### Ubuntu
```
sudo apt install libsdl2-dev libsdl2-mixer-dev

### Arch Linux
sudo pacman -S sdl2 sdl2_mixer

### To compile:
make

### run
./game



