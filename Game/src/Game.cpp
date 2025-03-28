#include "../includes/Game.h"
#include <iostream>
Game::Game()
{
    map = std::make_shared<Map>();
   

    std::vector<Vector2> poss = map.get()->getStartingPosition();
    Vector2 playerstartpos = poss[0];
    playerstartpos.x *= 100;
    playerstartpos.y *= 100 + 25;

    racers.push_back(new Player(playerstartpos, map, 7));

  /*   for(int i = 1; i < poss.size(); i++){
        Vector2 playerstartpos = poss[i];
        playerstartpos.x *= 100;
        playerstartpos.y *= 100 + 25;
        std::cout <<playerstartpos.x <<", "<<playerstartpos.y <<std::endl;
        racers.push_back(new AI(playerstartpos, map, i));
    } */
    deltaTime = 0.0f;
    collisionManager = CollisionManager();
}

Game::~Game()
{
    for(auto racer : racers){
        delete racer;
    }
    racers.clear();
}

void Game::display()
{
    map->draw();
    for(auto racer : racers){
        racer->draw(deltaTime);
    }
}

void Game::handleInput()
{
    if(IsKeyReleased(KEY_LEFT_CONTROL)){
        racers[0]->decelerate();
    }
    if(IsKeyDown(KEY_LEFT_CONTROL)){
        racers[0]->accelerate();
    }
    if(IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_LEFT_ALT)){
        racers[0]->decelerate(true);
    }
    if(IsKeyDown(KEY_LEFT)){
        racers[0]->turn(Direction::LEFT);
    }
    if(IsKeyDown(KEY_RIGHT)){
        racers[0]->turn(Direction::RIGHT);
    }
    if(IsKeyDown(KEY_LEFT_ALT)){
        racers[0]->changeGear();
    }
}

Vector2 Game::target()
{
    return racers[0]->target();
}

void Game::setDeltaTime(float t)
{
    deltaTime = t;
}

void Game::checkCollision()
{
    collisionManager.checkCollision(racers, map);
}
