#pragma once
#include"Player.h"
#include"Tile.h"
class Player;
class World
{
public:
vector<vector<Tile>> tile_grid;

World();
void LoadWorld();
void LoadWorld1();
void UnloadWorld();
void UpdateWorldData();
void DrawWorld(Vector2 playerposition);
};