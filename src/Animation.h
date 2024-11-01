#pragma once
#include"global.h"
class PlayerAnimation
{
public:
float target_time_frame;
float elapsedtime;
int currentframe;
vector<Texture2D> framelist;
Texture2D spritesheet;
int framecount;
//void Prepare(int l,int w,float target,Rectangle d,int start,int end,Texture2D* texture=NULL);
void animate(Rectangle& d,int dir,int framecount);
void animate64(Rectangle& d , int dir);
void Load64slow(AnimationIndex index);
void Load64fast(AnimationIndex index);
bool isOver();
void Reset();
void Loadp1_walk();
void Loadp2_walk();
void Loadp3_walk();
void Loadp1_idle();
void Loadp2_idle();
void Loadp3_idle();
void Unload();
~PlayerAnimation();
};