#include "includes/CollisionManager.h"
#include <iostream>
#include <cmath>
CollisionManager::CollisionManager()
{

}

void CollisionManager::checkCollision(std::vector<Racer*> &racers, const std::shared_ptr<Map> &m)
{
    for(auto racer : racers){

        checkCollisionWithMap(racer, m);
    }
}

void CollisionManager::checkCollisionWithMap(Racer *racer, const std::shared_ptr<Map> &m)
{

    std::shared_ptr<Car> car = racer->getCar();
    Vector2 position = car.get()->getPosition();
    Rectangle boundingBox = car.get()->getBoxCollision();

    size_t x = (size_t) std::ceil(boundingBox.x / 100);
    size_t y = (size_t) std::ceil(boundingBox.y / 100);

    const std::vector<std::vector<Element>>& elements = m.get()->getTilesElement();
    if(y > 1 && y < elements.size() -1 && x > 1 && x < elements[y].size() - 1){
        // check up 
        if( elements[y-1][x] == BLOCK ){
            std::cout <<"checking up" << std::endl;
            bool state =  CheckCollisionRecs(boundingBox, {(float)x, (float)(y-1) * 100, 100, 100});
            car->handleCollision(O_UP, state);
        }else{
            car->handleCollision(O_UP, false);
        }

        // check down 
        if(elements[y+1][x] == BLOCK ){
            std::cout <<"checking down" << std::endl;
            bool state =  CheckCollisionRecs(boundingBox, {(float)x, (float)(y+1) * 100, 100, 100});
            car->handleCollision(O_DOWN, state);
        }else{
            car->handleCollision(O_DOWN, false);
        }

        // check left 
        if(elements[y][x-1] == BLOCK ){
            std::cout <<"checking left" << std::endl;
            bool state =  CheckCollisionRecs(boundingBox, {(float)(x-1) * 100, (float)y * 100, 100, 100});
            car->handleCollision(O_LEFT, state);
        }else{
            car->handleCollision(O_LEFT, false);
        }

        // check right 
        if( elements[y][x+1] == BLOCK ){
            std::cout <<"checking right" << std::endl;
            bool state =  CheckCollisionRecs(boundingBox, {(float)(x+1) * 100, (float)y * 100, 100, 100});
            car->handleCollision(O_DOWN, state);
        }else{
            car->handleCollision(O_DOWN, false);
        }
    }
    

}

void CollisionManager::checkCoollisionWithCars(std::vector<Racer *> &racers)
{

}
