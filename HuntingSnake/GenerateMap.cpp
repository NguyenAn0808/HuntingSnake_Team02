#include "GenerateMap.h"


// ___________________________________________________________________MAP 2______________________________________________________________________

// Initialize obstacle for level 2
void create_obstacle_2(unsigned int x_pos, unsigned int y_pos, unsigned int height, unsigned int width, toado obs[], int& obs_nums) {
	int dist = 10;
	for (int i = x_pos + dist; i <= width - dist; i++) {
		obs[obs_nums].x = i;
		obs[obs_nums].y = x_pos + (height / 2) / 2 + 1;
		obs_nums++;

		obs[obs_nums].x = i;
		obs[obs_nums].y = x_pos + (height / 2) + (height / 2) - 1;
		obs_nums++;
	}
}

// Generate level 2
void play_match2(unsigned int x_pos, unsigned int y_pos, unsigned int height, unsigned int width, toado obs[], int obs_nums) {
	// prepare obstacle for level 2
	create_obstacle_2(x_pos, y_pos, height, width, obs, obs_nums);
	// draw match board
	draw_matchBoard(x_pos, y_pos, height, width);
	// draw obstacle for level 2
	draw_obstacle(obs, obs_nums);
}

// ___________________________________________________________________MAP 3______________________________________________________________________

// Initialize obstacle for level 3
void create_obstacle_3(unsigned int x_pos, unsigned int y_pos, unsigned int height, unsigned int width, toado obs[], int& obs_nums) {
	int dist = 10;
	for (int i = x_pos + dist; i <= width - dist; i++) {
		obs[obs_nums].x = i;
		obs[obs_nums].y = x_pos + (height / 2) / 2 + 1;
		obs_nums++;

		obs[obs_nums].x = i;
		obs[obs_nums].y = x_pos + (height / 2) + (height / 2) - 1;
		obs_nums++;
	}
	for (int j = y_pos + 8; j <= x_pos + (height / 2) + (height / 2) - 5; j++) {
		obs[obs_nums].x = x_pos + 2 * dist;
		obs[obs_nums].y = j;
		obs_nums++;

		obs[obs_nums].x = width - 2 * dist;
		obs[obs_nums].y = j;
		obs_nums++;
	}

}

// Generate level 3
void play_match3(unsigned int x_pos, unsigned int y_pos, unsigned int height, unsigned int width, toado obs[], int obs_nums) {
	// prepare obstacle for level 3
	create_obstacle_3(x_pos, y_pos, height, width, obs, obs_nums);
	// draw matchboard
	draw_matchBoard(x_pos, y_pos, height, width);
	// draw obstacle for level 2
	draw_obstacle(obs, obs_nums);
}



// ___________________________________________________________________MAP 4______________________________________________________________________

// Initialize obstacle for level 4
void create_obstacle_4(int x_pos, int y_pos, int width, int height, toado obs[], int& obs_nums, toado const_obs[], int& const_obs_nums)
{
	int obs_length = 10;
	for (int i = y_pos + 1; i <= y_pos + obs_length; i++)
	{
		obs[obs_nums].x = x_pos + width / 3;
		obs[obs_nums].y = i;
		obs_nums++;
	}

	for (int i = y_pos + height - obs_length; i <= y_pos + height - 1; i++)
	{
		obs[obs_nums].x = x_pos + 2 * (width / 3);
		obs[obs_nums].y = i;
		obs_nums++;
	}

	for (int i = x_pos + width / 2 - 4; i <= x_pos + width / 2 + 4; i++) {
		const_obs[const_obs_nums].x = i;
		const_obs[const_obs_nums].y = height / 2 + 4;
		const_obs_nums++;
	}

}

// Make obstacle move
void move_obs(int x_pos, int y_pos, int width, int height, toado obs[], int obs_nums, bool& up, toado const_obs[], int const_obs_nums)
{
	draw_obstacle(const_obs, const_obs_nums);
	if (up)
	{
		GotoXY(obs[obs_nums / 2 - 1].x, obs[obs_nums / 2 - 1].y);
		cout << " ";
		for (int i = 0; i < obs_nums / 2; i++)
		{
			obs[i].y--;
		}
		GotoXY(obs[0].x, obs[0].y);
		cout << char(219);

		GotoXY(obs[obs_nums / 2].x, obs[obs_nums / 2].y);
		cout << " ";
		for (int i = obs_nums / 2; i < obs_nums; i++)
		{
			obs[i].y++;
		}
		GotoXY(obs[obs_nums - 1].x, obs[obs_nums - 1].y);
		cout << char(219);

		if (obs[0].y == y_pos + 1)
		{
			up = false;
		}

	}
	else
	{
		GotoXY(obs[0].x, obs[0].y);
		cout << " ";

		for (int i = 0; i < obs_nums / 2; i++)
		{
			obs[i].y++;
		}

		GotoXY(obs[obs_nums / 2 - 1].x, obs[obs_nums / 2 - 1].y);
		cout << char(219);

		GotoXY(obs[obs_nums - 1].x, obs[obs_nums - 1].y);
		cout << " ";
		for (int i = obs_nums / 2; i < obs_nums; i++)
		{
			obs[i].y--;
		}
		GotoXY(obs[obs_nums / 2].x, obs[obs_nums / 2].y);
		cout << char(219);


		if (obs[obs_nums / 2 - 1].y == y_pos + height - 1)
		{
			up = true;
		}
	}
}

// Generate level 4
void play_match4(unsigned int x_pos, unsigned int y_pos, unsigned int height, unsigned int width, toado obs[], int obs_nums, bool up, toado const_obs[], int const_obs_nums) {
	// prepare obstacle for level 4
	create_obstacle_4(x_pos, y_pos, width, height, obs, obs_nums, const_obs, const_obs_nums);
	// draw match board
	draw_matchBoard(x_pos, y_pos, height, width);
	// Move obstacle
	while (true) {
		move_obs(x_pos, y_pos, width, height, obs, obs_nums, up, const_obs, const_obs_nums);
		// Set movable obstacle speed
		Sleep(65);
	}
}

//void create_obstacle_5(unsigned int x_pos, unsigned int y_pos, unsigned int height, unsigned int width, toado obs[], int& obs_nums) {}


void getConsoleSize(int& columns, int& rows)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	//printf("columns: %d\n", columns);
	//printf("rows: %d\n", rows);
}

void LoadMap()
{
	toado* obs;
	obs = new toado[1000];
	int obs_nums = 0;
	toado* const_obs;
	const_obs = new toado[500];
	int const_obs_nums = 0;
	bool up = false;
	//draw_matchBoard(1, 3, 22, 80);
	play_match2(1, 3, 23, 80, obs, obs_nums);
}