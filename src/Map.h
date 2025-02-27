#pragma once
#include "raylib.h"
#include <vector>

class Map
{
private:
    void load(std::string path);
    std::vector<std::vector<Texture2D>> tiles;
    Texture2D lines;
    Texture2D squares;
public:
    Map();
    ~Map();
    void draw();
};


