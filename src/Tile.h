#pragma once
#include"global.h"
class Tile
{
public:
    int texture_ID;
    Vector2 pos;
    int gridposx,gridposy;
    Rectangle dest;
    Rectangle Hitbox;
    bool islowerhalf;
    bool isupperhalf;
    Tile();
    void AssignPosition(int indexX,int indexY);
    void LoadData(unsigned int);
};