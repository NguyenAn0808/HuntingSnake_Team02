#pragma once
#include "ConsoleWindow.h"
#include <iostream>
#include <string>

enum colorCode
{
    BLACK,
    DARK_BLUE,
    DARK_GREEN,
    DARK_CYAN,
    DARK_RED,
    DARK_MAGENTA,
    DARK_YELLOW,
    LIGHT_GRAY,
    DARK_GRAY,
    LIGHT_BLUE,
    LIGHT_GREEN,
    LIGHT_CYAN,
    LIGHT_RED,
    LIGHT_MAGENTA,
    LIGHT_YELLOW,
    WHITE
};

// to draw a rectangle with user-choice color, text, text color
void draw_rectangle(unsigned int x_pos, unsigned int y_pos, unsigned int height, unsigned int width, int line_color, int bg_color, std::string text, int txtColor);
// set background color for the terminal
void setBackgroundColor(int bg_color);
// to higlight the button in rectangle shape, user can choose color base on the need
void highlightedBox(bool use, unsigned int x_pos, unsigned int y_pos, unsigned int height, unsigned int width, int bg_color, int line_color); 