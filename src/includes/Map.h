#pragma once
#include "raylib.h"
#include <vector>
#include <string>
#include "enums.h"

class Map
{
public:
    Map();
    ~Map();
    void draw();
    std::vector<Vector2> getStartingPosition();
    const std::vector<std::vector<Element>>& getTilesElement();
private:
    void load(std::string path);
    std::vector<std::vector<Element>> tilesElement;
    std::vector<std::vector<Texture2D>> tiles;
    
    Texture2D linesv;
    Texture2D linesh;
    Texture2D squares;
    Texture2D blocks;
    Texture2D voids;
    Texture2D trees;
    std::vector<Vector2> startingPosition;

};


