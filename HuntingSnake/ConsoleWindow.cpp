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

void LoadConsole()
{
    //set console 120x49
    //setWindowSize(120, 49);
    //setScreenBufferSize(120, 49);

    //set console maximize
    MaximizeConsoleWindow();

    DisableResizeWindow();
    DisableCtrButton(1, 1, 1);
    ShowScrollbar(0);
    SetConsolePosition(1, 1);
    LockConsolePosition();
    MaximizeConsoleWindow();

    //Pause the program to watch result
    system("pause");
}

void DisableResizeWindow()
{
    //get handle window console
    HWND hWnd = GetConsoleWindow();
    // don't allow to change size console through drag the edges or corners
    SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_SIZEBOX);
}

void DisableCtrButton(bool Close, bool Min, bool Max)
{
    //get handle window console
    HWND hWnd = GetConsoleWindow();
    //get menu of console
    HMENU hMenu = GetSystemMenu(hWnd, false);

    //1 - off, 0 - on
    if (Close == 1)
    {
        //delete close button
        DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);
    }
    if (Min == 1)
    {
        //delete min button
        DeleteMenu(hMenu, SC_MINIMIZE, MF_BYCOMMAND);
    }
    if (Max == 1)
    {
        //delete max button
        DeleteMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND);
    }
}

void ShowScrollbar(BOOL Show)
{
    HWND hWnd = GetConsoleWindow();
    //SB_BOTH to hide both horizontal & vertical scrollbars
    //0 - off, 1 - on
    ShowScrollBar(hWnd, SB_BOTH, Show);
}

void SetConsolePosition(int x, int y)
{
    HWND consoleWindow = GetConsoleWindow();
    SetWindowPos(consoleWindow, 0, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

void LockConsolePosition() {
    HWND consoleWindow = GetConsoleWindow();
    //get style window console
    LONG_PTR windowStyle = GetWindowLongPtr(consoleWindow, GWL_STYLE);

    // delete flag WS_CAPTION out of the window
    windowStyle &= ~WS_CAPTION;

    SetWindowLongPtr(consoleWindow, GWL_STYLE, windowStyle);

    // set size window
    SetWindowPos(consoleWindow, NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_FRAMECHANGED);
}

void MaximizeConsoleWindow()
{
    HWND consoleWindow = GetConsoleWindow();
    //set console at maximize size
    ShowWindow(consoleWindow, SW_MAXIMIZE);
}

void mainMenu() {
    // define parameters
    unsigned int x_menu = 50,
        y_menu = 5,
        rec_width = 20,
        rec_height = 4;
    
    setBackgroundColor(BG_COLOR);
    
    // draw menu
    draw_rectangle(x_menu, 5, rec_height, rec_width, 5, BG_COLOR, "New Game", 2);
    draw_rectangle(x_menu, 10, rec_height, rec_width, 4, BG_COLOR, "Load Game", 2);
    draw_rectangle(x_menu, 15, rec_height, rec_width, 2, BG_COLOR, "Achievements", 2);
    draw_rectangle(x_menu, 20, rec_height, rec_width, 3, BG_COLOR, "Settings", 2);
}