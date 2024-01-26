#include "ConsoleWindow.h"

void text_color(int background_color, int text_color)
{
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	int color_code = background_color * 16 + text_color;
	SetConsoleTextAttribute(color, color_code);
}

void GotoXY(int x, int y)
{
	COORD coord;

	coord.X = x;
	coord.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void mainMenu()
{
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	std::cout << "SNAKE GAME" << std::endl;
	draw_rec(5, 10, 5, 8, 0);
}
