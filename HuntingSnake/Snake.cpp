#include "Snake.h"
#include "ConsoleWindow.h"

// Random number generator (rng) object generates seed to random number [0, 2^64 - 1]
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

// Declare Global Variables, Structs
Point Snake[MAX_SIZE_SNAKE]; // Snake
Point Food[MAX_SIZE_FOOD]; // Food
Point Obs[MAX_SIZE_OBS]; // Obstacles
Point Center; // Center coordinates of Gate
Point Gate[5]; // Coordinates of Gate

string str[MAX_SIZE_SNAKE]; 

int STATE; // DEAD or ALIVE
int SPEED; // Current speed (Speed increase with each level)
int ID_Food; // Current index of food 
int ID_Obs; // Current index of obstacles 
int LEVEL = 1; // Current level (Maximum is 5 levels)
int TYPE; // Type of Gate (4 types directions = 4 types gates)
int cntGate; // index of coordinates of Gate
int Snake_Size; // Size of snake, initially 6 units and maximum is 22 units

char CHAR_LOCK; // At a moment, there is one direction that snake cannot move to
char MOVING; // At a moment, there are three directions that snake can move

bool GateDraw; // Gate exist or not

float addTime; // Control the speed between rows and columns 
// Speed through rows < speed through columns (number of columns > number of rows)

float DeltaSpeed = 0; // Control the speed when move to next level

void StartGame()
{
	system("cls"); // Clear screen
	ResetData(); // Intialize original data
	DrawBoard(0, 0, WIDTH_CONSOLE, HEIGH_CONSOLE); // Draw board matrix WIDTH * HEIGH with 4 boundaries
	STATE = 1; // ALIVE (Running thread)
 	DrawSnake(MSSV); // Draw snake with MSSV of four members in group
}
void LoadGame()
{
	thread thread_obj(ThreadFunction); // Create thread for snake
	HANDLE handle_thread_obj = thread_obj.native_handle(); // Take handle of thread

	while (true)
	{
		char temp = toupper(_getch()); // Get character from the keyboard (including 4 arrows, WASD)
		ResumeThread(handle_thread_obj); 

		// H, P, M, K -> 4 arrows when transform into characters
		if ((temp == 'W' || temp == 'S' || temp == 'A' || temp == 'D' ||
			temp == 'H' || temp == 'P' || temp == 'M' || temp == 'K') && temp != CHAR_LOCK)
		{
			MOVING = temp; // Next movement of snake
		}
	}
}

void ProcessDead()
{
	STATE = 0; // DEAD
	GotoXY(0, HEIGH_CONSOLE + 2);
	cout << "YOU LOSE";
}
void ResetData()
{
	//Initialize the global variables, structs
	for (int i = 0; i < cntGate; i++)
		Gate[i] = { 0, 0 };

	cntGate = 0;

	SPEED = 1;
	addTime = 0;
	Snake_Size = 6 + MAX_SIZE_FOOD * (LEVEL - 1);

	CHAR_LOCK = 'A';
	MOVING = 'D';
	 
	ID_Food = 0;

	int Init = HEIGH_CONSOLE / 2 + 5;

	//Initialize the coordinates of snake

	Snake[0] = { Init, Init };
	Snake[1] = { Init - 1, Init };
	Snake[2] = { Init - 2, Init };
	Snake[3] = { Init - 3, Init };
	Snake[4] = { Init - 4, Init };
	Snake[5] = { Init - 5, Init };

	GenerateFood(); // Create food array
}

void ThreadFunction(void)
{
	while (true)
	{
		if (STATE == 1) // If snake ALIVE -> continue
		{
			EraseOldPosition();
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

		DrawSnake(MSSV); // After one move, draw new snake because of the change of coordinates
		ProcessGate(); // Process if meet the conditions to create the gate
		//DrawObs();
		Sleep(100 / (SPEED + DeltaSpeed - addTime)); // Sleep function will set the speed of snake
	}
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
void DrawSnake(const string& str) // With str is MSSV
{
	// Draw head of snake
	GotoXY(Snake[0].x, Snake[0].y);
	text_color(0, 4); // Color of head will be different from body
	cout << str[0];

	for (int i = 1; i < Snake_Size; i++)
	{
		GotoXY(Snake[i].x, Snake[i].y);
		text_color(0, 10);
		cout << str[i]; // Draw body of snake
	}
}
void DrawFood()
{
	GotoXY(Food[ID_Food].x, Food[ID_Food].y);
	text_color(0, 10);
	cout << "O";
}
void DrawObs()
{
	GotoXY(Obs[ID_Obs].x, Obs[ID_Obs].y);
	text_color(0, 5);
	cout << "T";
}
void DrawGate(int x, int y)
{
	TYPE = Random(1, 4); // Random 4 types of gates

	switch (TYPE)
	{
		case 1:
			DrawGateU1(x, y, "o"); 
			break;
		case 2:
			DrawGateU2(x, y, "o");
			break;
		case 3:
			DrawGateU3(x, y, "o");
			break;
		case 4:
			DrawGateU4(x, y, "o");
			break;
	}

	GateDraw = true; // Gate exits
}
void DrawGateU1(int x, int y, const string& st)
{
	for (int i = -1; i <= 1; i++)
	{
		GotoXY(x + i, y);
		Gate[cntGate++] = { x + i, y }; // Save coordinates of each point from gate to array
		text_color(0, 4);
		cout << st;
	}

	GotoXY(x - 1, y - 1);
	Gate[cntGate++] = { x - 1, y - 1 };
	text_color(0, 4);
	cout << st;

	GotoXY(x + 1, y - 1);
	Gate[cntGate++] = { x + 1, y - 1 };
	text_color(0, 4);
	cout << st;
}
void DrawGateU2(int x, int y, const string& st)
{
	for (int i = -1; i <= 1; i++)
	{
		GotoXY(x + i, y);
		Gate[cntGate++] = { x + i, y };
		text_color(0, 4);
		cout << st;
	}

	GotoXY(x - 1, y + 1);
	Gate[cntGate++] = { x - 1, y + 1 };
	text_color(0, 4);
	cout << st;

	GotoXY(x + 1, y + 1);
	Gate[cntGate++] = { x + 1, y + 1 };
	text_color(0, 4);
	cout << st;
}
void DrawGateU3(int x, int y, const string& st)
{
	for (int i = -1; i <= 1; i++)
	{
		GotoXY(x, y + i);
		Gate[cntGate++] = { x, y + i};
		text_color(0, 4);
		cout << st;
	}

	GotoXY(x + 1, y - 1);
	Gate[cntGate++] = { x + 1, y - 1 };
	text_color(0, 4);
	cout << st;

	GotoXY(x + 1, y + 1);
	Gate[cntGate++] = { x + 1, y + 1 };
	text_color(0, 4);
	cout << st;
}
void DrawGateU4(int x, int y, const string &st)
{
	for (int i = -1; i <= 1; i++)
	{
		GotoXY(x, y + i);
		Gate[cntGate++] = { x, y + i };
		text_color(0, 4);
		cout << st;
	}

	GotoXY(x - 1, y - 1);
	Gate[cntGate++] = { x - 1, y - 1 };
	text_color(0, 4);
	cout << st;

	GotoXY(x - 1, y + 1);
	Gate[cntGate++] = { x - 1, y + 1 };
	text_color(0, 4);
	cout << st;
}

void ProcessGate()
{
	if (GateDraw == false) // If doesn't meet the conditions to create Gate -> continue draw food to eat food 
	{
		DrawFood(); // (4 foods each level to create Gate)
	}
	else // Create Gate already
	{
		if (TouchGate()) // When come into gate and crash it -> DEAD
		{
			ProcessDead();
			return;
		}

		if (Snake[0].x == Center.x && Snake[0].y == Center.y && Snake_Size > 0) // Snake come into gate
		{
			for (int i = 0; i < Snake_Size - 1; i++)
				Snake[i] = Snake[i + 1];

			Snake_Size--;
		}

		if (Snake_Size == 0) // When all the body of snake come into Gate -> Erase Gate and move to next level
		{
			// Erase Gate
			EraseGate();
			GateDraw = false; 

			DeltaSpeed += 0.3F; // Increase speed when move to next level
			LEVEL++; // Move to next level

			ResetData(); // Intialize original data when move to new level
		}
	}
}
void EraseGate()
{
	for (int i = 0; i < cntGate; i++)
	{
		GotoXY(Gate[i].x, Gate[i].y);
		cout << " ";
	}
}
void EraseOldPosition()
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
		} while (isValidFood(x, y) == false); // Check if can create food
		 
		Food[i] = { x, y }; // Random coordinates of food into array
	}
}
void EatFood()
{
	Snake[Snake_Size] = Food[ID_Food]; // Insert new size of body (Insert food coordinates)

	if (ID_Food == MAX_SIZE_FOOD - 1) // 4 foods can generate Gate
	{
		GenerateCenterGate();
		DrawGate(Center.x, Center.y); // Draw Gate
	}
	else // Increase size of snake, index of food
	{
		ID_Food++;
		Snake_Size++;	
		GenerateFood();
	}
}

bool isValidObs(int x, int y)
{
	for (int i = 0; i < ID_Food; i++)
	{
		if (Food[i].x == x && Food[i].y == y)
			return false;
	}

	for (int i = 0; i < Snake_Size; i++)
	{
		if (Snake[i].x == x && Snake[i].y == y)
			return false;
	}

	return true;
}
void GenerateObs(void)
{
	int x, y;
	for (int i = 0; i < MAX_SIZE_OBS; i++)
	{
		do
		{
			x = Random(1, WIDTH_CONSOLE - 1);
			y = Random(1, HEIGH_CONSOLE - 1);
		} while (isValidObs(x, y) == false);
		Obs[i] = { x, y };
	}
}
void GenerateCenterGate()
{
	int x, y;
	do
	{
		x = Random(2, WIDTH_CONSOLE - 2);
		y = Random(2, HEIGH_CONSOLE - 2);
	} while (CenterGate(x - 1, y) == false && CenterGate(x, y) == false && CenterGate(x + 1, y) == false 
		  && CenterGate(x - 1, y + 2) == false && CenterGate(x + 1, y + 2) == false); 
	// Check 5 * 5 matrix with center is Center Point Of Gate (avoid gate opposite the bound)
	// It makes sure that there are no Food, Obstacles and Snake in this 5x5 matrix

	Center = { x, y };
}

// 8 directions from point (x, y) 
int dx[] = { -1, 0, 0, 1, -1, -1, 1, 1 };
int dy[] = { 0, -1, 1, 0, -1, 1, -1, 1 };

bool CenterGate(int x, int y)
{
	if (TouchWall(x, y) == true)
		return false;

	for (int dir = 0; dir < 8; dir++) // Check 8 directions from Center Point of Gate (Not food, obstacles, snake, wall)
	{
		int new_x = x + dx[dir]; 
		int new_y = y + dy[dir];

		if (TouchWall(new_x, new_y) == true)
			return false;

		if (isValidFood(new_x, new_y) == false)
			return false;

		if (isValidObs(new_x, new_y) == false)
			return false;
	}

	return true;
}
bool TouchObs()
{
	for (int i = 0; i < MAX_SIZE_OBS; i++)
	{
		if (Snake[0].x == Obs[i].x && Snake[0].y == Obs[i].y)
			return true;
	}

	return false;
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
bool TouchGate()
{
	for (int i = 0; i < cntGate; i++)
	{
		if (Gate[i].x == Center.x && Gate[i].y == Center.y)
			continue;

		for (int j = 0; j < Snake_Size; j++)
		{
			if (Snake[j].x == Gate[i].x && Snake[j].y == Gate[i].y)
				return true;
		}
	}

	return false;
}

void MoveUp()
{
	if (TouchWall(Snake[0].x, Snake[0].y - 1) == true) // Touch the Wall -> You lose
	{
		ProcessDead();
		return;
	}

	if (Snake[0].x == Food[ID_Food].x && Snake[0].y - 1 == Food[ID_Food].y) // If move to coordinates of Food -> Eat Food
		EatFood();

	for (int i = Snake_Size - 2; i >= 0; i--) // Change the coordinates of Snake
		Snake[i + 1] = Snake[i];

	Snake[0].y--; // Move up

	if (TouchItself() || TouchObs()) // Check conditions to make sure that snake still ALIVE
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
	 
	Snake[0].y++; // Move down

	if (TouchItself() || TouchObs())
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

	Snake[0].x++; // Move right

	if (TouchItself() || TouchObs())
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

	Snake[0].x--; // Move left

	if (TouchItself() || TouchObs())
	{
		ProcessDead();
		return;
	}
}