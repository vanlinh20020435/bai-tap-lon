#ifndef THONGSO_H_INCLUDED
#define THONGSO_H_INCLUDED
#include<iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <fstream>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
using namespace std;
enum Color {
    blue,
    violet,
    cyan,
    green,
    orange,
    red,
    yellow,
    total
};

enum ManHinh{
    Logo,
    Play,
    Over,
    _Pause,
    Quit
};

enum Button{
    Right,
    Left,
    Down
};

enum TmpStyle{
    I,
    J,
    L,
    O,
    Z,
    T,
    S
};

const int MATRIX_DRAW_POS_X = 40;
const int MATRIX_DRAW_POS_Y = 0;
const int MATRIX_PIECES_X = 18;
const int MATRIX_PIECES_Y = 28;
const int SCREEN_WIDTH = 750;
const int SCREEN_HEIGHT = 600;
const int kmenunum=5;
const int star_x = ((MATRIX_PIECES_X-4)/2)*20+20+MATRIX_DRAW_POS_X;
const int star_y = 0;
const int dem_max=500;
#endif // THONGSO_H_INCLUDED
