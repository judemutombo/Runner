#include "includes/Car.h"
#include <iostream>
#include <cmath>
#include "raymath.h"
#include <sstream>

Car::Car( Vector2 position, const  std::shared_ptr<Map>& m, int choice) :
    position(position), rotation(0.0f), direction({1.0, 0.0}), map(m), rx(0.0), ry(0.0), choice(choice), gear(DRIVE)
{

    std::stringstream ss;

    ss << "resources/textures/cars" << std::to_string(choice) << ".png";
    
    Image image = LoadImage(ss.str().c_str());
    texture = LoadTextureFromImage(image);
    UnloadImage(image);
    deltaTime = 0.0f;
    currentTime = GetTime();
    previousTime = 0.0f;
    accTimer = 0.0f;
    accTimerController = 0.03;

    
    accController = 0.0005;
    accControllerLimit = 0.0005;
    
    rWidth = texture.width;
    rHeight = texture.height;
    update();
}

Car::~Car()
{
    UnloadTexture(texture);
}

void Car::draw(float t)
{
    deltaTime = t;
    update();
    Rectangle source = { 0.0f, 0.0f, (float)texture.width, (float)texture.height };
    Vector2 origin = { (float)(texture.width/2.0), (float)(texture.height /2.0) }; 
    
    Rectangle rec = {rx, ry, rWidth, rHeight};
    Color color;
    if(collisionSide[0]){
        color = RED;
    }else if(collisionSide[1]){
        color = YELLOW;
    }else if(collisionSide[2]){
        color = BLUE;
    }else if(collisionSide[3]){
        color = VIOLET;
    }else{
        color = GREEN;
    }


    DrawRectangleLinesEx(rec, 2, color);
    //std::cout<<rotation<<std::endl;
    DrawTexturePro(texture, source, (Rectangle){ position.x, position.y, texture.width, texture.height }, origin, rotation, WHITE);

    
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
        if(currentSpeed > MaxSpeed) currentSpeed = MaxSpeed;
        previousTime = currentTime;
        accTimer += accTimerController;
    }
}

void Car::accelerate2()
{
    currentTime = GetTime();
    if(0.3 <= currentTime - previousTime){
        currentSpeed += acc2;
        // std::cout <<"speed : " << currentSpeed <<std::endl;
        if(currentSpeed > MaxSpeed) currentSpeed = MaxSpeed;
        acc2 -= accController;
        if( acc2 < accControllerLimit) acc2 = accControllerLimit;
    }

}

void Car::decelerate(bool manual)
{
    if(manual){
        currentTime = GetTime();
        if(0.3 <= currentTime - previousTime){
            if( 0 <= currentSpeed){
                currentSpeed -= 0.05f;
                if(0 > currentSpeed ) currentSpeed =0.0f;
            }
        }
    }
    
    std::cout <<"speed : " << currentSpeed <<std::endl;
}

void Car::update()
{
    rotation = (atan2(direction.x, direction.y)* 180) / PI;


    float displacementX =(direction.x * currentSpeed * deltaTime);
    float displacementY = ((-direction.y) * currentSpeed * deltaTime);

    displacementX *= gear == DRIVE ? 1 : -1;
    displacementY *= gear == DRIVE ? 1 : -1;
    
    if(collisionSide[0] && (displacementY < 0)){
        position.x =  position.x + displacementX;
    }
    else if(collisionSide[1] && (displacementY > 0)){
        position.x =  position.x + displacementX;
    }
    else if(collisionSide[2] && (displacementX < 0)){
        position.y =  position.y + displacementY;
    }
    else if(collisionSide[3] && (displacementX > 0)){
        position.y =  position.y + displacementY;
    }
    else{
        position.x =  position.x + displacementX;
        position.y =  position.y + displacementY;
    }
    updateCollisionRec();
}

void Car::turn(Direction dir)
{
    float trn = (turnAmount * currentSpeed);
   if(dir == Direction::LEFT){
        if(1.0f == direction.y){
            direction.x -= trn;
            if(-1.0f > direction.x) direction.x = -1.0f;
        } if(-1.0f == direction.x){
            direction.y -= trn;
            if(-1.0f > direction.y) direction.y = -1.0f;
        }if(-1.0f == direction.y){
            direction.x += trn;
            if(1.0f < direction.x) direction.x = 1.0f;
        } if(1.0f == direction.x){
            direction.y += trn;
            if(1.0f < direction.y) direction.y = 1.0f;
        }
   }else if (dir == Direction::RIGHT){
        if(1.0f == direction.y){
            direction.x += trn;
            if(1.0f < direction.x) direction.x = 1.0f;
        } if(-1.0f == direction.x){
            direction.y += trn;
            if(1.0f < direction.y) direction.y = 1.0f;
        }if(-1.0f == direction.y){
            direction.x -= trn;
            if(-1.0f > direction.x) direction.x = -1.0f;
        } if(1.0f == direction.x){
            direction.y -= trn;
            if(-1.0f > direction.y) direction.y = -1.0f;
        }
    }
        
  // std::cout <<"x : " << direction.x <<" y : " << direction.y<<std::endl;
}

bool Car::collidesWith(const std::shared_ptr<Car> &anotherCar)
{
    return false;
}

void Car::handleCollision(Orientation orientation, bool state)
{
    switch (orientation)
    {
    case O_UP:
        collisionSide[0] = state;
        break;
    case O_DOWN:
        collisionSide[1] = state;
        break;
    case O_LEFT:
        collisionSide[2] = state;
        break;
    case O_RIGHT:
        collisionSide[3] = state;
        break;
    default:
        break;
    }
}

Vector2 Car::getPosition()
{
    return position;
}

Rectangle Car::getBoxCollision()
{
    return {rx, ry, rWidth, rHeight};
}

void Car::updateCollisionRec()
{

    // Convert rotation to radians
    float rad = rotation * (3.14 / 180.0f);

    // Get texture dimensions
    float w = texture.width;
    float h = texture.height;

    // Compute the bounding box dimensions for the rotated car
    rWidth = std::abs(w * cos(rad)) + std::abs(h * sin(rad));
    rHeight = std::abs(w * sin(rad)) + std::abs(h * cos(rad));

    // Keep collision rectangle centered on the car
    rx = position.x - (rWidth / 2.0f);
    ry = position.y - (rHeight / 2.0f);
}

void Car::changeGear(){
    if (currentSpeed <= 10)
        gear = DRIVE == gear ? REVERSE : DRIVE;
}