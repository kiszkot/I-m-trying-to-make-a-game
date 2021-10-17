#pragma once
#ifndef Map_hpp
#define Map_hpp

#include "Game.hpp"

class Map {

public:
    Map();
    ~Map();

    void LoadMap(int arr[20][25]);
    void DrawMap();

private:
    SDL_Rect srcStone, srcGrass, dest;

    SDL_Texture * sheet;

    int map[20][21];

};

#endif