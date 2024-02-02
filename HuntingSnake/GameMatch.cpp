#include "GameMatch.h"


void setTextColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void draw_rec(unsigned int x_pos, unsigned int y_pos, unsigned int height, unsigned int width)
{
	// if cannot draw => return
	if (height < 1 || width < 1) return;


	// draw a rectangle with border and no filling color
	for (int ix = x_pos + 1; ix < x_pos + width; ++ix) {
		GotoXY(ix, y_pos);
		cout << char(205);
		GotoXY(ix, y_pos + height);
		cout << char(205);
	}
	GotoXY(x_pos, y_pos);
	for (int iy = y_pos + 1; iy < y_pos + height; ++iy) {
		GotoXY(x_pos, iy);
		cout << char(186);
		GotoXY(x_pos + width, iy);
		cout << char(186);
	}
	GotoXY(x_pos, y_pos);
	cout << char(201);
	GotoXY(x_pos + width, y_pos);
	cout << char(187);
	GotoXY(x_pos, y_pos + height);
	cout << char(200);
	GotoXY(x_pos + width, y_pos + height);
	cout << char(188);
}

void draw_underline(unsigned int x_pos, unsigned int y_pos, unsigned int height, unsigned int width, string text, int txtColor, int bg_color, int line_color) {
	text_color(bg_color, txtColor);
	if (!text.empty()) {
		GotoXY(x_pos + (width - text.size()) / 2, y_pos + height / 2);
		std::cout << text;
	}
	text_color(bg_color, line_color);

	draw_rec(x_pos, y_pos, height, width);
}
//	draw_matchBoard(1, 3, 21, 80);
void draw_matchBoard(unsigned int x_pos, unsigned int y_pos, unsigned int height, unsigned int width) {
	GotoXY(x_pos + 20, y_pos - 2);
	/*
	*
	 ████████╗██╗   ██╗████████╗ ██████╗ ██████╗ ██╗ █████╗ ██╗
	 ╚══██╔══╝██║   ██║╚══██╔══╝██╔═══██╗██╔══██╗██║██╔══██╗██║
		██║   ██║   ██║   ██║   ██║   ██║██████╔╝██║███████║██║
		██║   ██║   ██║   ██║   ██║   ██║██╔══██╗██║██╔══██║██║
		██║   ╚██████╔╝   ██║   ╚██████╔╝██║  ██║██║██║  ██║███████╗
		╚═╝    ╚═════╝    ╚═╝    ╚═════╝ ╚═╝  ╚═╝╚═╝╚═╝  ╚═╝╚══════
	*/
	draw_rec(x_pos, y_pos, height, width);
	draw_infoBoard(width + 5, y_pos, height - 4, width - 48, 2, 0, 5);
	draw_underline(x_pos, height + 4, 2, width - 50, "MAP 1: ", 2, 0, 5);
	draw_underline(width - 50 + 2, height + 4, 2, width - (width - 50) - 1, "PLAYER: ", 2, 0, 5);
	draw_underline(width + 5, height, 3, width - 50 + 2, "SCORE: ", 2, 0, 5);
	draw_underline(width + 5, height + 4, 2, width - 50 + 2, "LEVEL 1: ", 2, 0, 5);

}
void draw_infoBoard(unsigned int x_pos, unsigned int y_pos, unsigned int height, unsigned int width, int txtColor, int bg_color, int line_color) {
	draw_rec(x_pos, y_pos, height, width);
	setTextColor(2);
	GotoXY(x_pos + 7, y_pos + 4); cout << "TUTORIAL";
	draw_underline(x_pos + 8, y_pos + 4, 2, 4, "W", txtColor, bg_color, line_color);
	draw_underline(x_pos + 2, y_pos + 7, 2, 4, "A", txtColor, bg_color, line_color);
	draw_underline(x_pos + 8, y_pos + 7, 2, 4, "S", txtColor, bg_color, line_color);
	draw_underline(x_pos + 14, y_pos + 7, 2, 4, "D", txtColor, bg_color, line_color);
	GotoXY(x_pos + 15, y_pos + 15); cout << "PAUSE: PRESS SPACE";
}


void draw_obstacle(Point obs[], int obs_nums) {
	for (int i = 0; i < obs_nums; i++) {
		GotoXY(obs[i].x, obs[i].y);
		cout << char(219);
	}
}

void draw_game(unsigned int x_pos, unsigned int y_pos, unsigned int height, unsigned int width, Point obs[], int obs_nums) {
	draw_matchBoard(x_pos, y_pos, height, width);
	draw_obstacle(obs, obs_nums);
}


