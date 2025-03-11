#pragma once
#include "raylib.h"
#include <vector>
#include <string>

class Map
{
public:
    Map();
    ~Map();
    void draw();
    std::vector<Vector2> getStartingPosition();
private:
    void load(std::string path);
    std::vector<std::vector<Texture2D>> tiles;
    
    Texture2D lines;
    Texture2D squares;
    Texture2D blocks;
    Texture2D voids;
    Texture2D trees;
    std::vector<Vector2> startingPosition;

};


