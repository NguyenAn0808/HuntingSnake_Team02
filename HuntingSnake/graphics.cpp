﻿#include "graphics.h"

void draw_rectangle(unsigned int x_pos, unsigned int y_pos, unsigned int height, unsigned int width, int line_color, int bg_color, std::string text, int txtColor)
{
	// if cannot draw => return
	if (height < 1 || width < 1) return;

	// print text if any
	text_color(bg_color, txtColor);
	if (!text.empty()) {
		GotoXY(x_pos + (width - text.size()) / 2, y_pos + height / 2);
		std::cout << text;
	}

	text_color(bg_color, line_color);

	// if user want to draw a color-only rectangle and no border
	if (bg_color != 0 && line_color != 0
		&& bg_color == line_color) {
		for (int iy = y_pos; iy <= y_pos + height; ++iy) {
			for (int ix = x_pos; ix <= x_pos + width; ++ix) {
				GotoXY(ix, iy);
				std::cout << char(219);
			}
		}
	}

	// draw a rectangle with border and no filling color
	else {
		for (int ix = x_pos + 1; ix < x_pos + width; ++ix) {
			GotoXY(ix, y_pos);
			std::cout << char(205);
			GotoXY(ix, y_pos + height);
			std::cout << char(205);
		}
		GotoXY(x_pos, y_pos);
		for (int iy = y_pos + 1; iy < y_pos + height; ++iy) {
			GotoXY(x_pos, iy);
			std::cout << char(186);
			GotoXY(x_pos + width, iy);
			std::cout << char(186);
		}
		GotoXY(x_pos, y_pos);
		std::cout << char(201);
		GotoXY(x_pos + width, y_pos);
		std::cout << char(187);
		GotoXY(x_pos, y_pos + height);
		std::cout << char(200);
		GotoXY(x_pos + width, y_pos + height);
		std::cout << char(188);
	}
	text_color(0, 7);

}

void setBackgroundColor(int bg_color)
{
	// get terminal's size
	CONSOLE_SCREEN_BUFFER_INFO info;
	int x, y;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	x = info.srWindow.Right - info.srWindow.Left + 1;
	y = info.srWindow.Bottom - info.srWindow.Top + 1;

	text_color(bg_color, bg_color);
	for (int i = 0; i <= x; ++i) {
		for (int j = 0; j <= y; ++j) {
			std::cout << char(219);
		}
	}
	text_color(0, 7);
}
