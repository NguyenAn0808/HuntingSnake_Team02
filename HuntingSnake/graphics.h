#pragma once
#include "ConsoleWindow.h"
#include <iostream>
#include <string>

void draw_rectangle(unsigned int x_pos, unsigned int y_pos, unsigned int height, unsigned int width, int line_color, int bg_color, std::string text, int txtColor);
void setBackgroundColor(int bg_color);