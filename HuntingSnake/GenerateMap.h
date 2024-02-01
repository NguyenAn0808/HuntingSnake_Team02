#pragma once
#include "ConsoleWindow.h"
#include "GameMatch.h"

// ___________________________________________________________________MAP 2______________________________________________________________________

void create_obstacle_2(unsigned int x_pos, unsigned int y_pos, unsigned int height, unsigned int width, toado obs[], int& obs_nums);

void play_match2(unsigned int x_pos, unsigned int y_pos, unsigned int height, unsigned int width, toado obs[], int obs_nums);

// ___________________________________________________________________MAP 3______________________________________________________________________

void create_obstacle_3(unsigned int x_pos, unsigned int y_pos, unsigned int height, unsigned int width, toado obs[], int& obs_nums);

void play_match3(unsigned int x_pos, unsigned int y_pos, unsigned int height, unsigned int width, toado obs[], int obs_nums);

// ___________________________________________________________________MAP 4______________________________________________________________________

void create_obstacle_4(int x_pos, int y_pos, int width, int height, toado obs[], int& obs_nums, toado const_obs[], int& const_obs_nums);

void move_obs(int x_pos, int y_pos, int width, int height, toado obs[], int obs_nums, bool& up, toado const_obs[], int const_obs_nums);

void play_match4(unsigned int x_pos, unsigned int y_pos, unsigned int height, unsigned int width, toado obs[], int obs_nums, bool up, toado const_obs[], int const_obs_nums);

// ___________________________________________________________________MAP 5______________________________________________________________________

//void create_obstacle_5(unsigned int x_pos, unsigned int y_pos, unsigned int height, unsigned int width, toado obs[], int& obs_nums);
void getConsoleSize(int& columns, int& rows);

void LoadMap(void);