#include "Snake.h"
#include "ConsoleWindow.h"

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

Point Snake[MAX_SIZE_SNAKE];
Point Food[MAX_SIZE_FOOD];

string str[MAX_SIZE_SNAKE];

int Snake_Size;

int STATE;
int SPEED;
int ID_Food;

char CHAR_LOCK;
char MOVING;

float addTime;

void StartGame()
{
	system("cls");
	ResetData();
	DrawBoard(0, 0, WIDTH_CONSOLE, HEIGH_CONSOLE);
	STATE = 1;
	DrawSnake(MSSV);
}

void LoadGame()
{
	thread thread_obj(ThreadFunction);
	HANDLE handle_thread_obj = thread_obj.native_handle();

	while (true)
	{
		char temp = toupper(_getch());
		ResumeThread(handle_thread_obj); // > 0

		if ((temp == 'W' || temp == 'S' || temp == 'A' || temp == 'D' ||
			temp == 'H' || temp == 'P' || temp == 'M' || temp == 'K') && temp != CHAR_LOCK)
		{
			MOVING = temp;
		}
	}
}

void ProcessDead()
{
	STATE = 0;
	GotoXY(0, HEIGH_CONSOLE + 2);
	cout << "YOU LOSE";
}

void ResetData()
{
	addTime = 0;
	SPEED = 1;
	Snake_Size = 6;

	CHAR_LOCK = 'A';
	MOVING = 'D';

	int Init = HEIGH_CONSOLE / 2 + 5;

	Snake[0] = { Init, Init };
	Snake[1] = { Init - 1, Init };
	Snake[2] = { Init - 2, Init };
	Snake[3] = { Init - 3, Init };
	Snake[4] = { Init - 4, Init };
	Snake[5] = { Init - 5, Init };

	GenerateFood();
}

void DrawBoard(int x, int y, int Width, int Heigh)
{
	GotoXY(x, y);
	cout << 'X';

	for (int i = 1; i <= Width; i++)
		cout << 'X';

	GotoXY(x, Heigh + y);
	cout << 'X';

	for (int i = 1; i <= Width; i++)
		cout << 'X';

	for (int j = y + 1; j < Heigh + y; j++)
	{
		GotoXY(x, j);
		cout << 'X';

		GotoXY(x + Width, j);
		cout << 'X';
	}

	GotoXY(0, 0);
}
void DrawSnake(const string& str)
{
	GotoXY(Snake[0].x, Snake[0].y);
	text_color(0, 4);
	cout << str[0];
	text_color(0, 7);

	for (int i = 1; i < Snake_Size; i++)
	{
		GotoXY(Snake[i].x, Snake[i].y);
		text_color(0, 10);
		cout << str[i];
		text_color(0, 7);
	}
}
void DrawFood()
{
	GotoXY(Food[ID_Food].x, Food[ID_Food].y);
	text_color(0, 10);
	cout << "O";
	text_color(0, 7);
}
void CleanOldPosition()
{
	for (int i = 0; i < Snake_Size; i++)
	{
		GotoXY(Snake[i].x, Snake[i].y);
		text_color(0, 10);
		cout << " ";
		text_color(0, 7);
	}
}

bool isValidFood(int x, int y)
{
	for (int i = 0; i < Snake_Size; i++)
	{
		if (Snake[i].x == x && Snake[i].y == y)
			return false;
	}

	return true;
}
void GenerateFood()
{
	int x, y;
	for (int i = 0; i < MAX_SIZE_FOOD; i++)
	{
		do
		{
			x = Random(1, WIDTH_CONSOLE - 1);
			y = Random(1, HEIGH_CONSOLE - 1);
		} while (isValidFood(x, y) == false);

		Food[i] = { x, y };
	}
}

void EatFood()
{
	Snake[Snake_Size] = Food[ID_Food];

	if (ID_Food == MAX_SIZE_FOOD - 1)
	{
		ID_Food = 0;
		Snake_Size = 6;

		SPEED = (SPEED == MAX_SPEED - 1 ? 1 : SPEED + 1);
		GenerateFood();
	}
	else
	{
		ID_Food++;
		Snake_Size++;
	}
}

void ThreadFunction(void)
{
	while (true)
	{
		if (STATE == 1)
		{
			CleanOldPosition();
			switch (MOVING)
			{
				// WASD Key

			case 'W':
			{
				MoveUp();
				CHAR_LOCK = 'S';
				addTime = 0.35F;
				break;
			}

			case 'S':
			{
				MoveDown();
				CHAR_LOCK = 'W';
				addTime = 0.35F;
				break;
			}

			case 'A':
			{
				MoveLeft();
				CHAR_LOCK = 'D';
				addTime = 0;
				break;
			}

			case 'D':
			{
				MoveRight();
				CHAR_LOCK = 'A';
				addTime = 0;
				break;
			}


			// Arrow Key
			case 'H':
			{
				MoveUp();
				CHAR_LOCK = 'P';
				addTime = 0.35F;
				break;
			}

			case 'P':
			{
				MoveDown();
				CHAR_LOCK = 'H';
				addTime = 0.35F;
				break;
			}

			case 'K':
			{
				MoveLeft();
				CHAR_LOCK = 'M';
				addTime = 0;
				break;
			}

			case 'M':
			{
				MoveRight();
				CHAR_LOCK = 'K';
				addTime = 0;
				break;
			}

			default:
				break;
			}
		}

		DrawSnake(MSSV);
		DrawFood();
		Sleep(100 / (SPEED - addTime));
	}
}

bool TouchWall(int x, int y)
{
	return !(x > 0 && x < WIDTH_CONSOLE && y > 0 && y < HEIGH_CONSOLE);
}
bool TouchItself()
{
	for (int i = 1; i < Snake_Size; i++)
		if (Snake[i].x == Snake[0].x && Snake[i].y == Snake[0].y)
			return true;

	return false;
}

void MoveUp()
{
	if (TouchWall(Snake[0].x, Snake[0].y - 1) == true)
	{
		ProcessDead();
		return;
	}

	if (Snake[0].x == Food[ID_Food].x && Snake[0].y - 1 == Food[ID_Food].y)
		EatFood();

	for (int i = Snake_Size - 2; i >= 0; i--)
		Snake[i + 1] = Snake[i];

	Snake[0].y--;

	if (TouchItself())
	{
		ProcessDead();
		return;
	}
}
void MoveDown()
{
	if (TouchWall(Snake[0].x, Snake[0].y + 1) == true)
	{
		ProcessDead();
		return;
	}

	if (Snake[0].x == Food[ID_Food].x && Snake[0].y + 1 == Food[ID_Food].y)
		EatFood();

	for (int i = Snake_Size - 2; i >= 0; i--)
		Snake[i + 1] = Snake[i];

	Snake[0].y++;

	if (TouchItself())
	{
		ProcessDead();
		return;
	}
}
void MoveRight()
{
	if (TouchWall(Snake[0].x + 1, Snake[0].y) == true)
	{
		ProcessDead();
		return;
	}

	if (Snake[0].x + 1 == Food[ID_Food].x && Snake[0].y == Food[ID_Food].y)
		EatFood();

	for (int i = Snake_Size - 2; i >= 0; i--)
		Snake[i + 1] = Snake[i];

	Snake[0].x++;

	if (TouchItself())
	{
		ProcessDead();
		return;
	}
}
void MoveLeft()
{
	if (TouchWall(Snake[0].x - 1, Snake[0].y) == true)
	{
		ProcessDead();
		return;
	}

	if (Snake[0].x - 1 == Food[ID_Food].x && Snake[0].y == Food[ID_Food].y)
		EatFood();

	for (int i = Snake_Size - 2; i >= 0; i--)
		Snake[i + 1] = Snake[i];

	Snake[0].x--;

	if (TouchItself())
	{
		ProcessDead();
		return;
	}
}