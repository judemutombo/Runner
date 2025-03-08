#pragma once
#include "raylib.h"
#include "raymath.h"

class Car
{
private:
    
    Vector2 position;
    Texture2D texture;
    float rotation;
    Vector2 direction;
    float MaxSpeed= 100.0f;
    float currentSpeed = 0.0f;
    float accTimer;
    float accTimerController;
    float accController;
    float accControllerLimit;
    float acc = 0.19; 
    bool accelerating; 
    float deltaTime;
    float currentTime;
    float previousTime;  
public:
    Car( Vector2 position);
    ~Car();
    void draw(float t);
    Vector2 target();
    void accelerate();
    void accelerate2();
    void decelerate(bool manual = false);
    void update();
};


