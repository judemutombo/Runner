#include "Map.h"
#include <fstream>
#include <string>


Map::Map()
{

}

Map::~Map()
{
    for (size_t i = 0; i < tiles.size(); i++){
        for (size_t j = 0; i < tiles[i].size(); i++){
            UnloadTexture(tiles[i][j]);
        }
    }
}

void Map::load(std::string path)
{
    
    Texture2D lines;
    Texture2D squares;
    Texture2D blocks;
    Texture2D voids;
    Texture2D trees;
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

            }else{
                row.push_back(voids);
            }
        }
        tiles.push_back(row);
        length++;
    }

    UnloadImage(imgL);
    UnloadImage(imgS);

    UnloadTexture(lines);
    UnloadTexture(blocks);
    UnloadTexture(voids);
    UnloadTexture(trees);
    UnloadTexture(squares);
}


void Map::draw()
{
    
}
