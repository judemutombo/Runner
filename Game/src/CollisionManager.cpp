#include "../includes/CollisionManager.h"
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

    size_t x = (size_t) customRound(boundingBox.x);
    size_t y = (size_t) customRound(boundingBox.y);
    
    
    // std::cout << "car position : [" << position.x <<", "<< position.y <<"]"<< std::endl;
    // std::cout << "box collision : [" << x <<", "<< y <<"]"<< std::endl;

    const std::vector<std::vector<Element>>& elements = m.get()->getTilesElement();
    if(y >= 0 && y < elements.size() -1 && x >= 0 && x < elements[y].size() - 1){
        // check up 
        DrawRectangleLinesEx({x * 100.0f,(y-1) * 100.0f, 100, 100}, 2, RED); 

        if(1 <= y && elements[y-1][x] == BLOCK ){
            // std::cout <<"checking up" << std::endl;
            bool state =  CheckCollisionRecs(boundingBox, {x * 100.0f,(y-1) * 100.0f, 100, 100});
            car->handleCollision(O_UP, state);
        }else{
            car->handleCollision(O_UP, false);
        }

        // check down 
        DrawRectangleLinesEx({x * 100.0f, (y+1) * 100.0f, 100, 100}, 2, YELLOW);
        if(elements[y+1][x] == BLOCK ){
            // std::cout <<"checking down" << std::endl;
            bool state =  CheckCollisionRecs(boundingBox, {x * 100.0f, (y+1) * 100.0f, 100, 100});
            car->handleCollision(O_DOWN, state);
        }else{
            car->handleCollision(O_DOWN, false);
        }

        // check left 
        DrawRectangleLinesEx({(x-1) * 100.0f, y * 100.0f, 100, 100}, 2, BLUE);
        if(1 <= x && elements[y][x-1] == BLOCK ){
            // std::cout <<"checking left" << std::endl;
            bool state =  CheckCollisionRecs(boundingBox, {(x-1) * 100.0f, y * 100.0f, 100, 100});
            car->handleCollision(O_LEFT, state);
        }else{
            car->handleCollision(O_LEFT, false);
        }

        // check right 
        DrawRectangleLinesEx({(x+1) * 100.0f, y * 100.0f, 100, 100}, 2, VIOLET);
        if( elements[y][x+1] == BLOCK ){
            // std::cout <<"checking right" << std::endl;
            bool state =  CheckCollisionRecs(boundingBox, {(x+1) * 100.0f, y * 100.0f, 100, 100});
            car->handleCollision(O_RIGHT, state);
        }else{
            car->handleCollision(O_RIGHT, false);
        }
    }
    

}

void CollisionManager::checkCoollisionWithCars(std::vector<Racer *> &racers)
{

}

float CollisionManager::customRound(float num) {
    float divided = num / 100.0f;
    float decimalPart = divided - std::floor(divided); 

    if (decimalPart > 0.5f) {
        return std::ceil(divided);
    } else {
        return std::floor(divided);
    }
}