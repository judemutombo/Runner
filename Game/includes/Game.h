#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include <iostream>
#include <vector>   
#include <ctime>
#include <memory>

#include "CollisionManager.h"
#include "Racer.h"
#include "Player.h"
#include "Map.h"
#include "AI.h"

class Game{
public:
    Game();
    ~Game();
    void display();
    void handleInput();
    Vector2 target();
    void setDeltaTime(float t);
    void checkCollision();
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
    std::shared_ptr<Map> map;  
    float deltaTime;
    std::vector<Racer*> racers;
    CollisionManager collisionManager;
};


#endif // GAME_H
