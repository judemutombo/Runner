#include "Player.h"
#include <iostream>


Player::Player(Vector2 position, const  std::shared_ptr<Map>& m)  :
    map(m)
{
    std::cout << "Player : Shared Pointer Count = " << map.use_count() << std::endl;
    car = new Car(position, m);
}

Player::~Player()
{
    delete car;
}

void Player::draw(float t)
{
    car->draw(t);
}

Vector2 Player::target()
{
    return car->target();
}

void Player::accelerate()
{
    car->accelerate();
}

void Player::decelerate(bool manual)
{
    car->decelerate(manual);
}

void Player::turn(Direction direction)
{
    car->turn(direction);
}
