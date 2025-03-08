#include "Car.h"
#include <iostream>
#include <cmath>



Car::Car( Vector2 position) :
 position(position), rotation(0.0f), direction({1, 0})
{
    Image image = LoadImage("resources/textures/cars7.png");
    texture = LoadTextureFromImage(image);
    UnloadImage(image);
    deltaTime = 0.0f;
    currentTime = GetTime();
    previousTime = 0.0f;
    accTimer = 0.0f;
    accTimerController = 0.03;

    
    accController = 0.0005;
    accControllerLimit = 0.0005;
}

Car::~Car()
{
    UnloadTexture(texture);
}

void Car::draw(float t)
{
    deltaTime = t;
    update();
    DrawTextureEx(texture, position, rotation, 1.0f, WHITE);  
}

Vector2 Car::target()
{
    return {(position.x + (texture.width/2)), (position.y + (texture.height/2))};
}

void Car::accelerate()
{
    currentTime = GetTime();
    if(accTimer <= currentTime - previousTime){
        currentSpeed += acc;
        std::cout <<"speed : " << currentSpeed <<std::endl;
        if(currentSpeed > MaxSpeed) currentSpeed = MaxSpeed;
        previousTime = currentTime;
        accTimer += accTimerController;
    }

}

void Car::accelerate2()
{
    currentTime = GetTime();
    if(0.3 <= currentTime - previousTime){
        currentSpeed += acc;
        std::cout <<"speed : " << currentSpeed <<std::endl;
        if(currentSpeed > MaxSpeed) currentSpeed = MaxSpeed;
        acc -= accController;
        if( acc < accControllerLimit) acc = accControllerLimit;
    }

}
void Car::decelerate(bool manual)
{
    std::cout<< "released" <<std::endl;
}

void Car::update()
{

    rotation = (atan2(direction.x, direction.y)* 180) / PI;

    position.x =  position.x + (direction.x * currentSpeed * deltaTime);
    position.y =  position.y + ((-direction.y) * currentSpeed * deltaTime);

}
