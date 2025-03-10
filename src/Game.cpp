#include "Game.h"
#include <iostream>
Game::Game()
{
    map = std::make_shared<Map>();
    std::cout << "Game : Shared Pointer Count = " << map.use_count() << std::endl;
    player = new Player({52, 25}, map);
    deltaTime = 0.0f;

}

Game::~Game()
{
    delete player;
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
