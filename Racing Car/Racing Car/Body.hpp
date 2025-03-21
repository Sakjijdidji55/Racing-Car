#ifndef BODY_HPP
#define BODY_HPP

#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include"Car.hpp"
#include"RoadLine.hpp"
#include"Queue.hpp"
#include"Coin.hpp"
#include<conio.h>
#include<time.h>
#include <graphics.h>

#define IMG_SIZE  128
#define ROW  6
#define COL  4
#define CountOfLines 18
#define MaxSpeed 24
#define DefaultSpeed 8
#define CountofCars 3
#define FPS 60
#define a 1
#define EXPLORESTATETIME 0.1
#define CountofCoins 6

#pragma comment(lib, "winmm.lib")



void initGame();

void UserStart();

void StartGame();

void update();

void isGameOver();

void CloseGame();

#endif 
