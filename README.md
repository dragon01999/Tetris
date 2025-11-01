# Terminal Tetris

A ncurses based Tetris clone written in C. Optional SDL music bgm included if SDL2 & SDL2_mixer are available.

## Controls
-> ← / →: Move left/right  
-> ↑: Rotate  
-> ↓: Soft drop  
-> Space: Hard drop  
-> P: Pause  
-> Q: Quit

## Building 
If Bgm is needed then:
To install them on Ubuntu:
sudo apt install libsdl2-dev libsdl2-mixer-dev libncurses-dev build-essential pkg-config
To install them on Arch Linux:
sudo pacman -S sdl2 sdl2_mixer

To compile:
make

To run:
./game



