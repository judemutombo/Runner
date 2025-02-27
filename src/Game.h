#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include <iostream>
#include <vector>   
#include <ctime>
#include "Player.h"
#include "Map.h"
class Game{
public:
    Game();
    ~Game();
    void display();
    void handleInput();
    Vector2 target();
private:
    // void drawMenu();
    // void drawPause();
    // void newGame();
    // void quitGame();
    // void win();
    
    bool won = false;
    bool onGoing = false;
    bool pause = false;
    bool gameOver = false;
    int winMenuChrono = 5;
    Player *player;
    Map *map;
};


#endif // GAME_H
