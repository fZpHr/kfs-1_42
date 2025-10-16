#include "include.h"

const char *giant_42[] = {
   "       ###     ++++::  ",
   "     ###     +++  ++::  ",
   "    ##++++      +::    ",
   "  ###  +     ++:       ",
   " ####++     ++:          ",
   "    #+     ++:            ",
   "  ##+    +++:::::::      ",
   " ##+    +++:::::::       ",
   "                         ",
};

void draw_42(int x, int y) {
    char *video = (char*)0xb8000;
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 24; ++col) {
            char c = giant_42[row][col];
            int offset = 2 * ((y + row) * VGA_WIDTH + (x + col));
            video[offset] = (c == ' ') ? ' ' : c;
            if (c == ':') {
                video[offset + 1] = RED_ON_BLACK;
            } else if (c == '#') {
                video[offset + 1] = BLUE_ON_BLACK;
            } else {
                video[offset + 1] = WHITE_ON_BLACK;
            }
        }
    }
}

void clear_screen() {
    char *video = (char*)0xb8000;
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; ++i) {
        video[2*i] = ' ';
        video[2*i+1] = WHITE_ON_BLACK;
    }
}