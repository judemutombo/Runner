#pragma once

#include "raylib.h"
#include "Car.h"
#include "enums.h"
class Player
{
private:
    Car *car;
public:
    Player( Vector2 position);
    ~Player();
    void draw(float t);
    Vector2 target();
    void accelerate();
    void decelerate(bool manual = false);
    void turn(Direction direction);
};

