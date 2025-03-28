#include "../includes/Player.h"
#include <iostream>


Player::Player(Vector2 position, const  std::shared_ptr<Map>& m, int choice)  :
    Racer(position, m, choice)
{
    
}


