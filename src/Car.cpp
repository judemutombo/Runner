#include "Car.h"
#include <iostream>
#include <cmath>
#include "functions.h"



Car::Car( Vector2 position, const  std::shared_ptr<Map>& m) :
    position(position), rotation(0.0f), direction({0.0, 1.0}), map(m), rx(0.0f), ry(0.0)
{
    std::cout << "Car : Shared Pointer Count = " << map.use_count() << std::endl;
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
    rx = position.x - (texture.width/2.0);
    ry = position.y - (texture.height /2.0);
    rWidth = texture.width  + abs(rotation);
    rHeight = texture.height + abs(rotation);
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
    DrawRectangleLinesEx(rec, 2, BLUE);
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

    position.x =  position.x + (direction.x * currentSpeed * deltaTime);
    position.y =  position.y + ((-direction.y) * currentSpeed * deltaTime);

}

void Car::turn(Direction dir)
{
    float trn = (turnAmount * 12);
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
    
    updateCollisionRec();
    
  // std::cout <<"x : " << direction.x <<" y : " << direction.y<<std::endl;
}

void Car::updateCollisionRec()
{
    if(135 <= rotation){
        rWidth = (float)texture.width + (abs(180 - rotation));
    }else if( -135 >= rotation){
        rWidth = (float)texture.width + (abs(180 + rotation));
    }else{
        rWidth = (float)texture.width + abs(rotation);
    }

    if(rWidth > texture.height){
        rWidth = texture.height;
    }else{
        if(135 <= rotation){
            rx = position.x - (texture.width/2.0) - (abs(180 - rotation)/2.0);
        }else if( -135 >= rotation){
            rx = position.x - (texture.width/2.0) - (abs(180 + rotation)/2.0);
        }else{
            rx = position.x - (texture.width/2.0) - (abs(rotation)/2.0);
        }
    }

    if(rotation > 45 && rotation < 90){
        rHeight = texture.height - abs(rotation - 45);
    }else if(rotation >= 90 && rotation <= 135){
        rHeight = texture.height - abs(rotation - 135);
    }

    std::cout<<"rotation : "<<rotation<<std::endl;
    std::cout<<"rHeight : "<<rHeight<<std::endl;
    if(rHeight < texture.width){
        rHeight = texture.width;
    }else{
        if(rotation > 45 && rotation < 90){
            ry = position.y - (texture.height /2.0) + (abs(rotation - 45)/2.0);
        }else if(rotation >= 90 && rotation <= 135){
            ry = position.y - (texture.height /2.0) + (abs(rotation - 135)/2.0);
        }
    }
}
