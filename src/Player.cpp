#include "Player.h"



Player::Player(Vector2 position) 
{

    car = new Car(position);
}

Player::~Player()
{
    delete car;
}

void Player::draw()
{
    car->draw();
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
