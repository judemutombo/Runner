#include "Car.h"
#include <iostream>

Car::Car( Vector2 position) :
 position(position), rotation(0.0f), direction({0, 1})
{
    Image image = LoadImage("resources/textures/cars7.png");
    texture = LoadTextureFromImage(image);
    UnloadImage(image);
}

Car::~Car()
{
    UnloadTexture(texture);
}

void Car::draw()
{
    DrawTextureEx(texture, position, rotation, 1.0f, WHITE);  
}

Vector2 Car::target()
{
    return {(position.x + (texture.width/2)), (position.y + (texture.height/2))};
}

void Car::accelerate()
{
    currentSpeed += acc;
    if(currentSpeed > MaxSpeed) currentSpeed = MaxSpeed;

}

void Car::decelerate(bool manual)
{
    std::cout<< "released" <<std::endl;
}
