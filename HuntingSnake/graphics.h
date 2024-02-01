#pragma once
#include "ConsoleWindow.h"
#include <iostream>
#include <string>
// use rgb color for text
#define SET_RGB(r, g, b) "\x1b[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m"
constexpr auto RGB_RESET = "\x1b[0m";

void draw_rectangle(unsigned int x_pos, unsigned int y_pos, unsigned int height, unsigned int width, int line_color, int bg_color, std::string text, int txtColor);
void setBackgroundColor(int bg_color, int txt_color);
void highlightedBox(bool use, unsigned int x_pos, unsigned int y_pos, unsigned int height, unsigned int width, int bg_color, int line_color);