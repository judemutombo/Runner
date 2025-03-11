#pragma once

#include "raylib.h"
#include "Car.h"
#include "enums.h"
#include "Map.h"
#include "Racer.h"
#include <memory>

class AI : public Racer{
public:
    AI( Vector2 position, const  std::shared_ptr<Map>& m, int choice);
};