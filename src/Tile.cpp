#include"Tile.h"
Tile::Tile()
{
    texture_ID=0;
    islowerhalf=false;
    isupperhalf=false;
}
void Tile::AssignPosition(int indexX,int indexY)
{
    gridposx=indexX;
    gridposy=indexY;
    pos.y=indexX*TILE_SIZE;
    pos.x=indexY*TILE_SIZE;
    dest.x=pos.x-TILE_SIZE/2;
    dest.y=pos.y-TILE_SIZE/2;
    dest.width=TILE_SIZE;
    dest.height=TILE_SIZE;
}
void Tile::LoadData(unsigned int ID)
{
    texture_ID=ID;
    Hitbox=dest;
    islowerhalf=IsLowerHalf(ID);
    isupperhalf=IsUpperHalf(ID);
    if(islowerhalf)
    {
        Hitbox.y=dest.y+dest.height/2;
        Hitbox.height/=2;
    }
    else if(isupperhalf)
    {
        Hitbox.height/=2;
    }

}