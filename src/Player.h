#pragma once

#include "raylib.h"
#include "Car.h"
class Player
{
private:
    Car *car;
public:
    Player( Vector2 position);
    ~Player();
    void draw();
    Vector2 target();
    void accelerate();
    void decelerate(bool manual = false);
};

