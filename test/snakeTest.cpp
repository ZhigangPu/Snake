#include "snake.h"
//#define TestReadCfg
//#define TestWhatTile
//#define TestWillDieOrNot
//#define TestCOV
//#define TestNF
//#define TestNewFruit
//#define TestUW
//#define TestNA
//#define TestGA
#define TestRun

int main(int argc, char **argv){
    Game game{};
    #ifdef TestReadCfg
    cout << "testing Readcfg() ..." << endl;
    ReadCfg(game);
    cout << "here is world layout" << endl;
    PrintWorld(game);
    cout << "here is initial velocity" << endl;
    cout << game.veclociy.dx << game.veclociy.dy << endl;
    cout << "here is snake position" << endl;
    for(auto &snakeElement : game.snake){
        cout << snakeElement.x << endl;
        cout << snakeElement.y << endl;
    }
    cout << "here is fruit position" << endl;
    cout << game.fruit.x << endl;
    cout << game.fruit.y << endl;
    #endif

    #ifdef TestWhatTile
    Point pt{3, 2};
    WorldTile tile = WhatTile(pt, game.world);
    cout << "tile: " << tile << endl;
    #endif
    
    #ifdef TestWillDieOrNot
    game.nextHead = Point{4,2};
    cout << "here is death prediction" << endl;
    cout << WillDieOrNot(game) <<  endl;
    #endif
    
    #ifdef TestCOV
    auto otherVelocity = ComputeOtherVelocity(game);
    cout << "here is other velocity possibility" << endl;
    for(auto& v : otherVelocity){
        cout << v.dx << v.dy << endl;
    }
    #endif

    #ifdef TestNF
    cout << "next is fruit? " << endl;
    game.nextHead = Point{2, 2};
    cout << NextIsFruit(game) << endl;
    #endif

    #ifdef TestNewFruit
    cout << "where is next fruit? " << endl;
    cout << "before" << endl;
    cout << game.fruit.x << game.fruit.y << endl;
    UpdateWorld(game, NFP);
    cout << game.fruit.x << " " << game.fruit.y << endl;
    #endif

    #ifdef TestUW
    PrintWorld(game);
    Point ptFront{8, 14};
    game.snake.push_front(ptFront);
    UpdateWorld(game                                                                   
drwxrwxr-x  6 ayron ayron 4.0K  6月 20 13:11 python_kafka                                                          │                                                                                                                   
drwxr-xr-x  7 ayron ayron 4.0K  6月 14 19:04 readinglist                                                           │                                              , ASH);
    UpdateWorld(game, CST);
    UpdateWorld(game, NFP);
    PrintWorld(game);
    #endif

    #ifdef TestNA
    game.nextHead = Point{2, 3};
    PerformNextAction(game);
    #endif

    #ifdef TestGA
    cout << "before GA" << endl;
    cout << game.nextHead.x << game.nextHead.y << endl;
    GenerateNextAction(game);
    cout << "After GA" << endl;
    cout << game.nextHead.x << game.nextHead.y << endl;
    #endif

    #ifdef TestRun
    RunGame();
    #endif


    return 0;
}