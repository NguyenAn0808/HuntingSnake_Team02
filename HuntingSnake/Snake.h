#pragma once
#include <iostream>
#include <random>
#include <chrono>
#include <conio.h>
#include <windows.h>
#include <string>
#include <thread>

#define Random(l, r) uniform_int_distribution<long long> (l, r) (rng)

using namespace std;

const int MAX_SIZE_FOOD = 4;
const int MAX_SIZE_SNAKE = 26;
const int MAX_SPEED = 5;
const int MAX_SIZE_OBS = 10;
const int MAX_LEVEL = 5;

const int WIDTH_CONSOLE = 100, HEIGH_CONSOLE = 20;

const string MSSV = "23127148231271522312744223127469";

struct Point
{
	int x;
	int y;
};

void StartGame(void);
void LoadGame(void);

void ProcessDead(void);
void ResetData(void);

void ThreadFunction(void);

void DrawBoard(int x, int y, int Width, int Heigh);
void DrawSnake(const string& s);
void DrawFood(void);
void DrawObs(void);
void DrawGate(int x, int y);
void DrawGateU1(int x, int y);
void DrawGateU2(int x, int y);
void DrawGateU3(int x, int y);
void DrawGateU4(int x, int y);

void CleanOldPosition(void);

bool isValidFood(int x, int y);
void GenerateFood(void);
void EatFood(void);

bool isValidObs(int x, int y);
void GenerateObs(void);
Point GenerateCenterGate(void);

bool CenterGate(int x, int y);
bool PassLevel(int x, int y);
bool TouchObs(void);
bool TouchWall(int x, int y);
bool TouchItself(void);

void MoveUp(void);
void MoveDown(void);
void MoveRight(void);
void MoveLeft(void);
