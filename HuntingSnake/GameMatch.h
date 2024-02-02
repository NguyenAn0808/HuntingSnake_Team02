#pragma once
#include "ConsoleWindow.h"
#include "Snake.h"
#include <iostream>

using namespace std;

void setTextColor(int color);

void draw_rec(unsigned int x_pos, unsigned int y_pos, unsigned int height, unsigned int width);

void draw_matchBoard(unsigned int x_pos, unsigned int y_pos, unsigned int height, unsigned int width);

void draw_infoBoard(unsigned int x_pos, unsigned int y_pos, unsigned int height, unsigned int width, int txtColor, int bg_color, int line_color);

void draw_underline(unsigned int x_pos, unsigned int y_pos, unsigned int height, unsigned int width, string text, int txtColor, int bg_color, int line_color);

void draw_obstacle(Point obs[], int obs_nums);

void draw_game(unsigned int x_pos, unsigned int y_pos, unsigned int height, unsigned int width, Point obstacle[], int obs_nums);

