#pragma once
#include"global.h"
#include"World.h"
#include"Animation.h"
class World;
class Player
{
public:
    Rectangle Hitbox_Rec;
    Circle Hitbox_Circ;
    Rectangle dest;
    Vector2 pos;
    Vector2 prevpos;
    int tileposrow,tileposcol;
    bool on_ground;
    bool landing;
    bool jumping;
    float speed_x;
    float speed_y;
    int direction;
    World* world;
    PlayerAnimation walk;
    PlayerAnimation idle;
    PlayerAnimation fall;
    PlayerAnimation land;
    PlayerAnimation jump;
    PlayerAnimation crouch;
    PlayerAnimation crawl;
    PlayerAnimation punch;

    queue<AnimationIndex> animations;
    float locktime;
    Player();
    void Reset();
    void UpdateData(World* w);
    void DrawData();
    void UpdateHitbox();
    void Updatedest();
    void UpdateTilepos();
    void UpdatePositionData();
    int footcollision();
    int torsocollision();
    int headcollision();
    int leftcollision();
    int rightcollision();
    int anycollision();
    void Unclipfeet();
    void Uncliphead();
    void Uncliptorso();
    void CheckBelow();
    ~Player();
};