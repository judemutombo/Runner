#include "Map.h"
#include <fstream>
#include <string>


Map::Map()
{

}

Map::~Map()
{
    UnloadTexture(lines);
    UnloadTexture(squares);
}

void Map::load(std::string path)
{
    Image imgL = LoadImage("resources/textures/road3.png");
    Image imgS = LoadImage("resources/textures/road4.png");

    lines = LoadTextureFromImage(imgL);
    squares = LoadTextureFromImage(imgS);

    int width, length;
    width = length = 0;

    std::fstream file;
    file.open(path);

    std::string line;

    while(std::getline(file, line)){
        if(line.size() >= width ){
            width = line.size();
        }
        for (size_t i = 0; i < line.size(); i++)
        {
            if(line[i] == '#'){
                tiles[length].push_back(imgL);
            }
        }
        
        length++;
    }

    UnloadImage(imgL);
    UnloadImage(imgS);
}


void Map::draw()
{

}
