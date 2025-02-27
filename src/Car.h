#pragma once
#include "raylib.h"

class Car
{
private:
    
    Vector2 position;
    Texture2D texture;
    float rotation;
    Vector2 direction;
    float MaxSpeed= 2.0f;
    float currentSpeed = 0.0f;
    float acc = 0.002; 
    bool accelerating; 
public:
    Car( Vector2 position);
    ~Car();
    void draw();
    Vector2 target();
    void accelerate();
    void decelerate(bool manual = false);
};


