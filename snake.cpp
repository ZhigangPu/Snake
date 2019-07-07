#include "snake.h"

void ReadCfg(Game& game) {
    string filename;
    cout << "please enter filename: " << endl;
    cin >> filename;

    ifstream infile;
    infile.open(filename);
    if(!infile.is_open()){
        cerr << "open " << filename << " failed!" << endl;
    }

    infile >> game.veclociy.dx >> game.veclociy.dy;
    cout << "read in initial veclocity: (" << game.veclociy.dx << ", " << game.veclociy.dy << ")" << endl;

    string oneLine;
    vector<string>::size_type lineNum{};
    while(getline(infile, oneLine)){
        lineNum++;
        game.world.push_back(oneLine);
        if(oneLine.find("*") != string::npos){
            string::size_type snakePostion = oneLine.find("*");
            game.snake.push_back(Point{lineNum, snakePostion});
        }
        if(oneLine.find("8") != string::npos){
            string::size_type fruitPostion = oneLine.find("8");
            game.fruit = Point{lineNum, fruitPostion};
        }

    }
    cout << "complete reading layout." << endl;
}

void PrintWorld(Game &game) {
    const string kClearCommand = "clear";
    system(kClearCommand.c_str());
    for (auto& row : game.world){
        cout << row << endl;
    }
}


WorldTile WhatTile (Point& pt, vector<string>& world) {
    char element = world[pt.x][pt.y];
    WorldTile tile;
    if (element == '#') tile = WALL;
    else if (element == '*') tile = BODY;
    else if (element == '8') tile = FRUIT;
    else tile = SPACE;
    return tile;

}


bool WillDieOrNot(Game& game){
    WorldTile nextTile = WhatTile(game.nextHead, game.world);
    if (nextTile == WALL | nextTile == BODY) return true;
    else if (nextTile == FRUIT | nextTile == SPACE) return false;
}

vector<Velocity> ComputeOtherVelocity(Game& game){
    vector<Velocity> otherPossibleVeclocity;
    if(game.veclociy.dx){
        otherPossibleVeclocity.push_back(Velocity{!game.veclociy.dx, !game.veclociy.dy * -1});
        otherPossibleVeclocity.push_back(Velocity{!game.veclociy.dx, !game.veclociy.dy * 1});
    }
    else if(game.veclociy.dy){
        otherPossibleVeclocity.push_back(Velocity{!game.veclociy.dx * -1, !game.veclociy.dy});
        otherPossibleVeclocity.push_back(Velocity{!game.veclociy.dx * 1, !game.veclociy.dy});
    }
    return otherPossibleVeclocity;
}

bool NextIsFruit(Game& game){
    WorldTile nextTile = WhatTile(game.nextHead, game.world);
    if (nextTile == FRUIT) return true;
    else return false;
}

void GenerateNewFruit(Game& game){
    game.worldWidth = game.world[0].size();
    std::default_random_engine e;
    std::uniform_int_distribution<unsigned> randomX(0, game.worldHeight);                   
    std::uniform_int_distribution<unsigned> randomY(0, game.worldWidth);                   
    while (true)
    {
        Point newFruit{randomX(e), randomY(e)};
        WorldTile tile = WhatTile(newFruit, game.world);
        if (tile == SPACE ) 
        {
            game.fruit = newFruit;
            break;
        } 
        else continue;
    }
}

void UpdateWorld(Game& game, WorldOperation op){
    switch (op)
    {
    case ASH:
    {
        deque<Point>::iterator iterSnakeBegin = game.snake.begin();
        game.world[iterSnakeBegin->x][iterSnakeBegin->y] = '*';
        break;
    }
    case CST:
    {
        deque<Point>::iterator iterSnakeEnd = game.snake.end();
        iterSnakeEnd--;
        game.world[iterSnakeEnd->x][iterSnakeEnd->y] = ' ';
        break;
    }
    case NFP:
    {
        game.world[game.fruit.x][game.fruit.y] = ' ';
        GenerateNewFruit(game);
        break;
    }
    default:
        break;
    }
}

/**
 * 更新蛇的位置，如果吃到了果子，尾巴不去，头部增加一个位置，并且随机生成下一个果子的位置；如果没有吃到，头部增加一个，尾部也去除一个。
 */
void PerformNextAction(Game& game){
    bool eatenOrNot = NextIsFruit(game);
    if(!eatenOrNot){
        game.snake.push_front(game.nextHead);
        UpdateWorld(game, ASH);
        UpdateWorld(game, CST);
        game.snake.pop_back();
    }
    else{
        game.snake.push_front(game.nextHead);
        UpdateWorld(game, ASH);
        UpdateWorld(game, NFP);
    }
    PrintWorld(game);
}

/**
 * 生成下一步的头部位置。策略如下： 如果当前速度方向不出问题，就按照当前速度方向走，如果当前速度方向有问题，就在另外两个方向之间选择，都不行游戏结束。
 */
bool GenerateNextAction(Game& game){
    vector<Velocity> otherPossibleVelocity = ComputeOtherVelocity(game);
    for(int i = 0; i < 3; i++){
        game.nextHead.x = game.snake.front().x + game.veclociy.dx;
        game.nextHead.y = game.snake.front().y + game.veclociy.dy;
        
        bool willDie = WillDieOrNot(game);
        if(willDie && i != 2) {
            game.veclociy = otherPossibleVelocity[i];
            continue;
        } ;
        if(willDie && i == 2) return false;

        return true;
    }
}

bool Initialize(Game& game){
    ReadCfg(game);
}

void StartGame(Game& game){
    while(true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        if(GenerateNextAction(game)) PerformNextAction(game);
        else {
            cout << "Game over, thanks for watching!" << endl;
            break;
        }
   }

}

void RunGame() {
    Game game{};
    
    Initialize(game);    
    RunGame(game);
}
