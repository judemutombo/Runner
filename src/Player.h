#pragma once

#include "raylib.h"
#include "Car.h"
#include "enums.h"
#include "Map.h"
#include <memory>

class Player
{
private:
    Car *car;
    std::shared_ptr<Map> map;
public:
    Player( Vector2 position, const  std::shared_ptr<Map>& m);
    ~Player();
    void draw(float t);
    Vector2 target();
    void accelerate();
    void decelerate(bool manual = false);
    void turn(Direction direction);
    
};

