#pragma once
#include <windows.h>

void text_color(int background_color, int text_color);

void GotoXY(int x, int y);

void LoadConsole();
void DisableResizeWindow();
void DisableCtrButton(bool Close, bool Min, bool Max);
void ShowScrollbar(BOOL Show);
void SetConsolePosition(int x, int y);
void LockConsolePosition();
void MaximizeConsoleWindow();