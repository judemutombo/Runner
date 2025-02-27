#include "Game.h"
#include <iostream>
Game::Game()
{
    player = new Player({52, 25});
    map = new Map();
}

Game::~Game()
{
    delete player;
    delete map;
}

void Game::display()
{
    map->draw();
    player->draw();
}

void Game::handleInput()
{
    if(IsKeyReleased(KEY_LEFT_CONTROL)){
        player->decelerate();
    }
    if(IsKeyDown(KEY_LEFT_CONTROL)){
        player->accelerate();
    }
    if(IsKeyDown(KEY_DOWN)){
        player->decelerate(true);
    }
    if(IsKeyDown(KEY_LEFT)){
    }
    if(IsKeyDown(KEY_RIGHT)){
    }
}

Vector2 Game::target()
{
    return player->target();
}
