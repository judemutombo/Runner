#include "Game.h"
#include <iostream>
Game::Game()
{
    player = new Player({52, 25});
    map = new Map();
    deltaTime = 0.0f;
}

Game::~Game()
{
    delete player;
    delete map;
}

void Game::display()
{
    map->draw();
    player->draw(deltaTime);
}

void Game::handleInput()
{
    if(IsKeyReleased(KEY_LEFT_CONTROL)){
        player->decelerate();
    }
    if(IsKeyDown(KEY_LEFT_CONTROL)){
        player->accelerate();
    }
    if(IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_LEFT_ALT)){
        player->decelerate(true);
    }
    if(IsKeyDown(KEY_LEFT)){
        player->turn(Direction::LEFT);
    }
    if(IsKeyDown(KEY_RIGHT)){
        player->turn(Direction::RIGHT);
    }
}

Vector2 Game::target()
{
    return player->target();
}

void Game::setDeltaTime(float t)
{
    deltaTime = t;
}
