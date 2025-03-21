#ifndef SOURCES_HPP
#define SOURCES_HPP

#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include"Car.hpp"
#include"RoadLine.hpp"
#include"Queue.hpp"
#include"Coin.hpp"
#include<conio.h>
#include<time.h>

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

void StartMusic();

void CloseMusic();

void WriteScore();

void WriteBlood();

void WriteBlood();

void LoadSource();

void LoadBackGround();

void DrawBackGround();

void initLines();

void DrawLines();

void ChangeLines();

void initPlayer(int id);

void DrawPlayer();

void MovePlayer();

void initEnemy();

void DrawEnemy();

void MoveEnemy();

void EnemysisCrash();

void IsShouldExplore();

void initCoins();

void MoveCoins();

void DrawCoins();

void EatCoins();

void CoinsisCrash();

#endif 