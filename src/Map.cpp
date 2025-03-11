#include "includes/Map.h"
#include <fstream>
#include <iostream>

Map::Map()
{
    load("resources/maps/kin.map");
}

Map::~Map()
{
    UnloadTexture(lines);
    UnloadTexture(blocks);
    UnloadTexture(voids);
    UnloadTexture(trees);
    UnloadTexture(squares);
}

void Map::load(std::string path)
{
    
    Image imgL = LoadImage("resources/textures/road3.png");
    Image imgS = LoadImage("resources/textures/road4.png");
    Image imgB = LoadImage("resources/textures/blocks.png");
    Image imgV = LoadImage("resources/textures/void.png");
    Image imgT = LoadImage("resources/textures/tree.png");

    lines = LoadTextureFromImage(imgL);
    squares = LoadTextureFromImage(imgS);
    blocks = LoadTextureFromImage(imgB);
    voids = LoadTextureFromImage(imgV);
    trees = LoadTextureFromImage(imgT);

    int width, length;
    width = length = 0;

    std::fstream file;
    file.open(path);

    std::string line;

    while(std::getline(file, line)){
        if(line.size() >= width ){
            width = line.size();
        }
        std::vector<Texture2D> row;
        for (size_t i = 0; i < line.size(); i++)
        {
            if(line[i] == '#'){
                row.push_back(blocks);
            }else if(line[i] == '+'){
                row.push_back(lines);
            }else if(line[i] == '*'){
                row.push_back(trees);
            }else if(line[i] == 's'){
                row.push_back(squares);
                startingPosition.push_back(Vector2{(float)i, (float)length});
            }else{
                row.push_back(voids);
            }
        }
        tiles.push_back(row);
        length++;
    }

    UnloadImage(imgL);
    UnloadImage(imgS);


    file.close();
}


void Map::draw()
{
    
    for (size_t i = 0; i < tiles.size(); i++) { 
        for (size_t j = 0; j < tiles[i].size(); j++) {     
            DrawTextureEx(tiles[i][j], {100.0f * j, 100.0f * i}, 0, 1.0f, WHITE); 
        }
    }
     
}

std::vector<Vector2> Map::getStartingPosition()
{
    return startingPosition;
}
