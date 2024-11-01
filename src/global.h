#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <raylib.h>
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <algorithm>
#include <unordered_map>
#include <queue>
using namespace std;

enum AnimationIndex
{
    CLIMB_BACK,
    CRAWL,
    CROUCH,
    DEATH,
    DOWN_SMASH,
    DOWN_TILT,
    F_SMASH,
    F_TILT,
    FALL,
    FLOATING_FALL,
    FLOATING_FLAP,
    FULL,
    GRAB,
    HIT,
    IDLE,
    INHALE_FLOAT,
    INHALE_START,
    INHALING,
    JUMP,
    JUMP_FALL_LAND,
    LAND,
    LEDGE_GRAB,
    LEFT_JAB,
    MULTI_JUMP,
    RIGHT_HOOK,
    RIGHT_LEFT_COMBO,
    ROLL_1,
    ROLL_2,
    SHIELD,
    U_SMASH,
    U_TILT,
    WALK,
    WALL_HIT,
    WALL_SLIDE

};
// Screen constants
constexpr int SCREEN_WIDTH = 1600;
constexpr int SCREEN_HEIGHT = 900;
constexpr int TILE_SIZE = 70;
constexpr int SCREEN_WIDTH_TILES=SCREEN_WIDTH/TILE_SIZE;
constexpr int SCREEN_HEIGHT_TILES=SCREEN_HEIGHT/TILE_SIZE;
constexpr float BACKGROUND_SPEED=3;

extern unordered_map<int,Texture2D> TILE_MAPPER;
extern unordered_map<int,int> SAFE_TILES;
extern unordered_map<int,int> HARMFUL_TILES;
extern unordered_map<int,int> UPPER_HALF_TILES;
extern unordered_map<int,int> LOWER_HALF_TILES;
extern unordered_map<AnimationIndex,std::string> PLAYER_ANIMATION_MAP;

// Player variables (declarations)
extern float PLAYER_SPEED;
extern float GRAVITY;
extern float PLAYER_INITIAL_X;
extern float PLAYER_INITIAL_Y;
extern float PLAYER_DEST_WIDTH;
extern float PLAYER_DEST_HEIGHT;
extern float PLAYER_HITBOX_WIDTH;
extern float PLAYER_HITBOX_HEIGHT;
extern float PLAYER_HITBOX_RADIUS;
extern float PLAYER_JUMP;
extern int COLLISION_RANGE;
extern int WORLD_WIDTH_TILES;
extern int WORLD_HEIGHT_TILES;

// Keyboard keys
extern KeyboardKey MOVE_RIGHT;
extern KeyboardKey MOVE_LEFT;
extern KeyboardKey MOVE_UP;
extern KeyboardKey MOVE_DOWN;
extern KeyboardKey PUNCH;


void LoadTileMapper();
void UnloadTileMapper();
void PrepareAnimationMap();
bool IsInsideWorld(Vector2 pos);
bool IsTileSafe(int);
bool IsTileHarmful(int);
bool IsLowerHalf(int);
bool IsUpperHalf(int);

struct Circle{
float x;
float y;
float r;
};
#endif CONSTANTS_H
