#include "../includes/Racer.h"


Racer::Racer(Vector2 position, const std::shared_ptr<Map> &m, int choice) :
    map(m), isColliding(false)
{
    car = std::make_shared<Car>(position, m, choice);
}

void Racer::draw(float t)
{
    car.get()->draw(t);
}

Vector2 Racer::target()
{
    return car.get()->target();
}

void Racer::accelerate()
{
    car.get()->accelerate();
}

void Racer::decelerate(bool manual)
{
    car.get()->decelerate(manual);
}

void Racer::turn(Direction direction)
{
    car.get()->turn(direction);
}
std::shared_ptr<Car> Racer::getCar()
{
    return car;
}
bool Racer::collidesWith(const Racer& anotherRacer)
{
    return car.get()->collidesWith(anotherRacer.car);
}

void Racer::handleCollision(Orientation orientation, bool state)
{
    return car.get()->handleCollision(orientation, state);
}

void Racer::changeGear()
{
    car.get()->changeGear();
}
