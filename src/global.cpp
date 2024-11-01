#include "global.h"

// Player variables (definitions)
float PLAYER_SPEED = 500.0f;
float GRAVITY=3000.0f;
float PLAYER_INITIAL_X =WORLD_WIDTH_TILES*TILE_SIZE/20; 
float PLAYER_INITIAL_Y =(WORLD_HEIGHT_TILES-10.0f)*TILE_SIZE;
float PLAYER_DEST_WIDTH = 256.0f;
float PLAYER_DEST_HEIGHT = 256.0f;
float PLAYER_HITBOX_WIDTH = PLAYER_DEST_WIDTH/4;
float PLAYER_HITBOX_HEIGHT = PLAYER_DEST_HEIGHT/8;
float PLAYER_JUMP = 1500.0f;
float PLAYER_HITBOX_RADIUS = PLAYER_DEST_WIDTH/10;
int COLLISION_RANGE=3;
int WORLD_WIDTH_TILES=200;
int WORLD_HEIGHT_TILES=18;

unordered_map<int,Texture2D> TILE_MAPPER;
unordered_map<int,int> SAFE_TILES;
unordered_map<int,int> HARMFUL_TILES;
unordered_map<int,int> UPPER_HALF_TILES;
unordered_map<int,int> LOWER_HALF_TILES;
unordered_map<AnimationIndex,std::string> PLAYER_ANIMATION_MAP;

// Keyboard keys (definitions)
KeyboardKey MOVE_RIGHT = KEY_RIGHT;
KeyboardKey MOVE_LEFT = KEY_LEFT;
KeyboardKey MOVE_UP = KEY_UP;
KeyboardKey MOVE_DOWN = KEY_DOWN;
KeyboardKey PUNCH=KEY_E;


void LoadTileMapper()
{
    TILE_MAPPER.insert(make_pair(65,LoadTexture("Tiles/grassCenter.png")));
    TILE_MAPPER.insert(make_pair(82,LoadTexture("Tiles/grassMid.png")));
    TILE_MAPPER.insert(make_pair(173,LoadTexture("Items/spikes.png")));
    TILE_MAPPER.insert(make_pair(77,LoadTexture("Tiles/grassMid.png")));
    TILE_MAPPER.insert(make_pair(78,LoadTexture("Tiles/grassCenter.png")));
    TILE_MAPPER.insert(make_pair(75,LoadTexture("Tiles/grassMid.png")));
    TILE_MAPPER.insert(make_pair(76,LoadTexture("Tiles/grassCenter.png")));
    TILE_MAPPER.insert(make_pair(1,LoadTexture("Tiles/boxAlt.png")));
    TILE_MAPPER.insert(make_pair(128,LoadTexture("Tiles/signRight.png")));
    TILE_MAPPER.insert(make_pair(58,LoadTexture("Tiles/door_closedMid.png")));
    TILE_MAPPER.insert(make_pair(59,LoadTexture("Tiles/door_closedTop.png")));
    TILE_MAPPER.insert(make_pair(126,LoadTexture("Tiles/signExit.png")));
    TILE_MAPPER.insert(make_pair(60,LoadTexture("Tiles/door_openMid.png")));
    TILE_MAPPER.insert(make_pair(61,LoadTexture("Tiles/door_openTop.png")));
    TILE_MAPPER.insert(make_pair(66,LoadTexture("Tiles/grassMid.png")));
    TILE_MAPPER.insert(make_pair(83,LoadTexture("Tiles/grassMid.png")));
    TILE_MAPPER.insert(make_pair(81,LoadTexture("Tiles/grassMid.png")));
    SAFE_TILES.insert(make_pair(128,1));
    SAFE_TILES.insert(make_pair(126,1));
    SAFE_TILES.insert(make_pair(58,1));
    SAFE_TILES.insert(make_pair(59,1));
    SAFE_TILES.insert(make_pair(60,1));
    SAFE_TILES.insert(make_pair(61,1));
    SAFE_TILES.insert(make_pair(0,1));
    SAFE_TILES.insert(make_pair(-1,1));
    //SAFE_TILES.insert(make_pair(77,1));
    //SAFE_TILES.insert(make_pair(75,1));
    HARMFUL_TILES.insert(make_pair(173,1));
    LOWER_HALF_TILES.insert(make_pair(173,1));
    LOWER_HALF_TILES.insert(make_pair(61,1));
    LOWER_HALF_TILES.insert(make_pair(59,1));
    //LOWER_HALF_TILES.insert(make_pair(77,1));
    //LOWER_HALF_TILES.insert(make_pair(75,1));

}
void UnloadTileMapper()
{
    for(auto it=TILE_MAPPER.begin();it!=TILE_MAPPER.end();it++)
    {
        UnloadTexture(it->second);
    }
}
void PrepareAnimationMap()
{
    PLAYER_ANIMATION_MAP.insert(make_pair(CLIMB_BACK,"Ducky/Spritesheets/climb_back.png"));
    PLAYER_ANIMATION_MAP.insert(make_pair(CRAWL,"Ducky/Spritesheets/crawl.png"));
    PLAYER_ANIMATION_MAP.insert(make_pair(CROUCH,"Ducky/Spritesheets/crouch.png"));
    PLAYER_ANIMATION_MAP.insert(make_pair(DEATH,"Ducky/Spritesheets/death.png"));
    PLAYER_ANIMATION_MAP.insert(make_pair(DOWN_SMASH,"Ducky/Spritesheets/down_smash.png"));
    PLAYER_ANIMATION_MAP.insert(make_pair(DOWN_TILT,"Ducky/Spritesheets/down_tilt.png"));
    PLAYER_ANIMATION_MAP.insert(make_pair(F_SMASH,"Ducky/Spritesheets/f_smash.png"));
    PLAYER_ANIMATION_MAP.insert(make_pair(F_TILT,"Ducky/Spritesheets/f_tilt.png"));
    PLAYER_ANIMATION_MAP.insert(make_pair(FALL,"Ducky/Spritesheets/fall.png"));
    PLAYER_ANIMATION_MAP.insert(make_pair(FLOATING_FALL,"Ducky/Spritesheets/floating_fall.png"));
    PLAYER_ANIMATION_MAP.insert(make_pair(FLOATING_FLAP,"Ducky/Spritesheets/floating_flap.png"));
    PLAYER_ANIMATION_MAP.insert(make_pair(FULL,"Ducky/Spritesheets/full.png"));
    PLAYER_ANIMATION_MAP.insert(make_pair(GRAB,"Ducky/Spritesheets/grab.png"));
    PLAYER_ANIMATION_MAP.insert(make_pair(HIT,"Ducky/Spritesheets/hit.png"));
    PLAYER_ANIMATION_MAP.insert(make_pair(IDLE,"Ducky/Spritesheets/idle.png"));
    PLAYER_ANIMATION_MAP.insert(make_pair(INHALE_FLOAT,"Ducky/Spritesheets/inhale_float.png"));
    PLAYER_ANIMATION_MAP.insert(make_pair(INHALE_START,"Ducky/Spritesheets/inhale_start.png"));
    PLAYER_ANIMATION_MAP.insert(make_pair(INHALING,"Ducky/Spritesheets/inhaling.png"));
    PLAYER_ANIMATION_MAP.insert(make_pair(JUMP,"Ducky/Spritesheets/jump.png"));
    PLAYER_ANIMATION_MAP.insert(make_pair(JUMP_FALL_LAND,"Ducky/Spritesheets/jump_fall_land.png"));
    PLAYER_ANIMATION_MAP.insert(make_pair(LAND,"Ducky/Spritesheets/land.png"));
    PLAYER_ANIMATION_MAP.insert(make_pair(LEDGE_GRAB,"Ducky/Spritesheets/ledge_grab.png"));
    PLAYER_ANIMATION_MAP.insert(make_pair(LEFT_JAB,"Ducky/Spritesheets/left_jab.png"));
    PLAYER_ANIMATION_MAP.insert(make_pair(MULTI_JUMP,"Ducky/Spritesheets/multi_jump.png"));
    PLAYER_ANIMATION_MAP.insert(make_pair(RIGHT_HOOK,"Ducky/Spritesheets/right_hook.png"));
    PLAYER_ANIMATION_MAP.insert(make_pair(RIGHT_LEFT_COMBO,"Ducky/Spritesheets/right_left_combo.png"));
    PLAYER_ANIMATION_MAP.insert(make_pair(ROLL_1,"Ducky/Spritesheets/roll_1.png"));
    PLAYER_ANIMATION_MAP.insert(make_pair(ROLL_2,"Ducky/Spritesheets/roll_2.png"));
    PLAYER_ANIMATION_MAP.insert(make_pair(SHIELD,"Ducky/Spritesheets/shield.png"));
    PLAYER_ANIMATION_MAP.insert(make_pair(U_SMASH,"Ducky/Spritesheets/u_smash.png"));
    PLAYER_ANIMATION_MAP.insert(make_pair(U_TILT,"Ducky/Spritesheets/u_tilt.png"));
    PLAYER_ANIMATION_MAP.insert(make_pair(WALK,"Ducky/Spritesheets/walk.png"));
    PLAYER_ANIMATION_MAP.insert(make_pair(WALL_HIT,"Ducky/Spritesheets/wall_hit.png"));
    PLAYER_ANIMATION_MAP.insert(make_pair(WALL_SLIDE,"Ducky/Spritesheets/wall_slide.png"));
}

bool IsInsideWorld(Vector2 pos)
{
    if(pos.x<0 || pos.x>WORLD_WIDTH_TILES*TILE_SIZE)
        return false;
    if(pos.y<-WORLD_HEIGHT_TILES*TILE_SIZE/4 || pos.y>WORLD_HEIGHT_TILES*TILE_SIZE)
        return false;
    return true;
    
}
bool IsTileSafe(int tile)
{
    if(SAFE_TILES.find(tile)!=SAFE_TILES.end())
        return true;
    return false;
}
bool IsTileHarmful(int tile)
{
    if(HARMFUL_TILES.find(tile)!=HARMFUL_TILES.end())
        return true;
    return false;
}
bool IsLowerHalf(int tile)
{
    if(LOWER_HALF_TILES.find(tile)!=LOWER_HALF_TILES.end())
        return true;
    return false;
}
bool IsUpperHalf(int tile)
{
    if(UPPER_HALF_TILES.find(tile)!=UPPER_HALF_TILES.end())
        return true;
    return false;
}
