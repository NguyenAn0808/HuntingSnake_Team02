#pragma once
#include <iostream>
#include <random>
#include <chrono>
#include <conio.h>
#include <windows.h>
#include <string>
#include <thread>

// Statements to random number in range [l, r] 
#define Random(l, r) uniform_int_distribution<long long> (l, r) (rng)

using namespace std;

// CONSTANTS
const int MAX_SIZE_FOOD = 2;
const int MAX_SIZE_SNAKE = 30;
const int MAX_SPEED = 5;
const int MAX_SIZE_OBS = 10;
const int MAX_LEVEL = 5;

const int WIDTH_CONSOLE = 100, HEIGH_CONSOLE = 20;

const string MSSV = "23127148231271522312744223127469";

// Declare struct Point2D
struct Point
{
	int x;
	int y;
};

void StartGame(void);// Function StartGame
void LoadGame(void);// Function LoadGame (movement of snake using keyboard)

void ProcessDead(void);// Function handle when snake DEAD
void ResetData(void);// Function Intialize original data

void ThreadFunction(void);// Subfunction for thread

void DrawSnake(const string& s);// Function Draw Snake
void DrawFood(void);// Function Draw Food
void DrawObs(void); // Function Draw Obstacles
void DrawGate(int x, int y);// Function Draw Gate
void DrawGateU1(int x, int y, const string& st); // Functio Draw Gate Type 1
void DrawGateU2(int x, int y, const string& st); // Functio Draw Gate Type 2
void DrawGateU3(int x, int y, const string& st); // Functio Draw Gate Type 3
void DrawGateU4(int x, int y, const string& st); // Functio Draw Gate Type 4

void ProcessGate(void); // Function Process Gate
void EraseGate(); //Function Erase Gate
void EraseOldPosition(void); //Function Erase Old Snake (Old coordinates)

bool isValidFood(int x, int y);// Function check if can create food
void GenerateFood(void); // Function Generate Food
void EatFood(void); // Function Eat Food
 
bool isValidObs(int x, int y); // Function check if can create obstacles
void GenerateObs(void); // Function Generate Obstalces
void GenerateCenterGate(void); // Function Generate Center Point of Gate

bool CenterGate(int x, int y); // Function check if can create Center Point of Gate
bool TouchObs(void); // Function check if snake touches obstacles
bool TouchGate(void); // Function check if snake touches Gate
bool TouchWall(int x, int y); // Function check if snake touches wall
bool TouchItself(void); // Function check if head of snake touches the body

void MoveUp(void); // Fucntion Move Up
void MoveDown(void); // Function Move Down
void MoveRight(void); // Function Move Right
void MoveLeft(void); // Function Move Left
