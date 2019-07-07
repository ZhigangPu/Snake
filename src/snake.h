#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <deque>
#include <random>
#include <chrono>
#include <thread>
#include <ctime>

using std::deque;
using std::string;
using std::vector;
using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std::ifstream;

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    short dx;
    short dy;
} Velocity;

typedef struct {
    Velocity veclociy;
    Point fruit; 
    Point nextHead;
    deque<Point> snake;
    vector<string> world;
    vector<string>::size_type worldHeight;
    string::size_type worldWidth;
    int eatenFruitNum = 0;
} Game;

typedef enum {
    FRUIT,
    WALL,
    BODY,
    SPACE
} WorldTile;

typedef enum {
    ASH, // add snake head
    CST, // cut snake tail
    NFP  // new fuit postion
} WorldOperation;


void ReadCfg(Game& game); 

void PrintWorld(Game &game);

WorldTile WhatTile (Point& pt, vector<string>& world); 

bool WillDieOrNot(Game& game);

vector<Velocity> ComputeOtherVelocity(Game& game);

bool NextIsFruit(Game& game);

void GenerateNewFruit(Game& game);

void UpdateWorld(Game& game, WorldOperation op);

/**
 * 更新蛇的位置，如果吃到了果子，尾巴不去，头部增加一个位置，并且随机生成下一个果子的位置；如果没有吃到，头部增加一个，尾部也去除一个。
 */
void PerformNextAction(Game& game);

/**
 * 生成下一步的头部位置。策略如下： 如果当前速度方向不出问题，就按照当前速度方向走，如果当前速度方向有问题，就在另外两个方向之间选择，都不行游戏结束。
 */
bool GenerateNextAction(Game& game);

bool Initialize(Game& game);

void RunGame();
