#pragma once
#include <windows.h>
#include <iostream>
#include <conio.h>
#include "Snake.h"
#include "graphics.h"
#define BG_COLOR 1
#define TXT_COLOR 7

struct terminalSize
{
	int x;
	int y;
};

terminalSize getTermSize();

void text_color(int background_color, int text_color);

void GotoXY(int x, int y);

void LoadConsole();
void DisableResizeWindow();
void DisableCtrButton(bool Close, bool Min, bool Max);
void ShowScrollbar(BOOL Show);
void SetConsolePosition(int x, int y);
void LockConsolePosition();
void MaximizeConsoleWindow();
void ShowConsoleCursor(bool show);

void mainMenu();