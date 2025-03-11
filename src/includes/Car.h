#pragma once
#include "raylib.h"
#include "raymath.h"
#include "enums.h"
#include "Map.h"
#include <memory>

class Car
{
public:
    Car( Vector2 position,const  std::shared_ptr<Map>& m, int choice);
    ~Car();
    void draw(float t);
    Vector2 target();
    void accelerate();
    void accelerate2();
    void decelerate(bool manual = false);
    void update();
    void turn(Direction dir);
    bool collidesWith(const std::shared_ptr<Car> &anotherCar);
    
private:
    int choice;
    std::shared_ptr<Map> map;
    Vector2 position;
    Texture2D texture;
    float rotation;
    Vector2 direction;
    float MaxSpeed= 200.0f;
    float currentSpeed = 0.0f;
    float accTimer;
    float accTimerController;
    float accController;
    float accControllerLimit;
    float acc = 4.9f; 
    float acc2 = 0.19f; 
    bool accelerating; 
    float deltaTime;
    float currentTime;
    float previousTime;  
    float turnAmount = 0.000005;

    float rx;
    float rWidth;

    float ry;
    float rHeight;
    void updateCollisionRec();

};


