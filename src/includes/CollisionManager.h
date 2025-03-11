#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include <vector>
#include "Racer.h"
#include "Map.h"

class CollisionManager{

public:
    CollisionManager();
    void checkCollision(std::vector<Racer*>& racers, const std::shared_ptr<Map> &m);
private:

};

#endif // COLLISIONMANAGER_H