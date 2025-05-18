#ifndef RACER_H
#define RACER_H

#include "raylib.h"
#include "Car.h"
#include "enums.h"
#include "Map.h"
#include <memory>
#include <string_view>
#include "../../Network/include/NetUdpClient.h"
#include "../../Network/include/packet.h"


class Racer{

public :
    Racer( Vector2 position, const  std::shared_ptr<Map>& m, int choice); 
    void draw(float t);
    Vector2 target();
    void accelerate();
    void decelerate(bool manual = false);
    void turn(Direction direction);
    std::shared_ptr<Car> getCar();
    bool collidesWith(const Racer& anotherRacer);
    void handleCollision(Orientation orientation, bool state);
    void changeGear();
    void getId(std::string_view c_id);
    void sendPosition();
protected:
    std::shared_ptr<Car> car;
    std::shared_ptr<Map> map;
    bool isColliding;
    std::string id;
    NetUdpClient client;
};

#endif // RACER_H