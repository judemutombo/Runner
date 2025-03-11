#include "includes/CollisionManager.h"
#include <iostream>
CollisionManager::CollisionManager()
{

}

void CollisionManager::checkCollision(std::vector<Racer*> &racers, const std::shared_ptr<Map> &m)
{
    std::cout << racers.size() << std::endl;
} 
