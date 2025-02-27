#pragma once
#include "raylib.h"
#include <vector>

class Map
{
private:
    void load(std::string path);
    std::vector<std::vector<Texture2D>> tiles;
public:
    Map();
    ~Map();
    void draw();
};


