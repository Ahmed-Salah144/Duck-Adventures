#include"Animation.h"
/*void PlayerAnimation::Prepare(int l,int w,float target,Rectangle d,int start,int end,Texture2D* texture)
{
    spritesheetptr=texture;
    sheetlengthframes=l;
    sheetwidthframes=w;
    target_time=target;
    dest=d;
    startframe=start;
    endframe=end;
    elapsedtime=0;
}*/
void PlayerAnimation::animate(Rectangle& d,int dir,int framecount)
{
    elapsedtime+=GetFrameTime();
    if(elapsedtime>target_time_frame)
    {
        elapsedtime=0.0f;
        currentframe=(currentframe+1)%framecount;
    }
    DrawTexturePro(framelist[currentframe],{0,0,dir*72.0f,97},d,{0,0},0.0f,WHITE);
}
void PlayerAnimation::animate64(Rectangle& d , int dir)
{
    elapsedtime+=GetFrameTime();
    if(elapsedtime>target_time_frame)
    {
        elapsedtime=0.0f;
        currentframe=(currentframe+1)%framecount;
    }
    DrawTexturePro(spritesheet,{currentframe*64.0f,0,dir*64.0f,64},d,{0,0},0.0f,WHITE);
}
void PlayerAnimation::Load64fast(AnimationIndex index)
{
    spritesheet=LoadTexture(PLAYER_ANIMATION_MAP[index].c_str());
    framecount=spritesheet.width/64;
    target_time_frame=0.075f;
    elapsedtime=0.0f;
    currentframe=0;
}
void PlayerAnimation::Load64slow(AnimationIndex index)
{
    spritesheet=LoadTexture(PLAYER_ANIMATION_MAP[index].c_str());
    framecount=spritesheet.width/64;
    target_time_frame=0.2f;
    elapsedtime=0.0f;
    currentframe=0;
}
bool PlayerAnimation::isOver()
{
    if(currentframe==framecount-1 && elapsedtime>target_time_frame*0.75)
    {    
        currentframe=0;
        elapsedtime=0;
        return true;
    }
    return false;
}
void PlayerAnimation::Reset()
{
    currentframe=0;
    elapsedtime=0;
}
void PlayerAnimation::Loadp1_walk()
{
    framelist.push_back(LoadTexture("Player/p1_walk/PNG/p1_walk01.png"));
    framelist.push_back(LoadTexture("Player/p1_walk/PNG/p1_walk02.png"));
    framelist.push_back(LoadTexture("Player/p1_walk/PNG/p1_walk03.png"));
    framelist.push_back(LoadTexture("Player/p1_walk/PNG/p1_walk04.png"));
    framelist.push_back(LoadTexture("Player/p1_walk/PNG/p1_walk05.png"));
    framelist.push_back(LoadTexture("Player/p1_walk/PNG/p1_walk06.png"));
    framelist.push_back(LoadTexture("Player/p1_walk/PNG/p1_walk07.png"));
    framelist.push_back(LoadTexture("Player/p1_walk/PNG/p1_walk08.png"));
    framelist.push_back(LoadTexture("Player/p1_walk/PNG/p1_walk09.png"));
    framelist.push_back(LoadTexture("Player/p1_walk/PNG/p1_walk10.png"));
    framelist.push_back(LoadTexture("Player/p1_walk/PNG/p1_walk11.png"));
    framelist.push_back(LoadTexture("Player/p1_walk/PNG/p1_walk01.png"));
    target_time_frame=0.1f;
    elapsedtime=0.0f;
    currentframe=0;
}
void PlayerAnimation::Loadp2_walk()
{
    framelist.push_back(LoadTexture("Player/p2_walk/PNG/p2_walk01.png"));
    framelist.push_back(LoadTexture("Player/p2_walk/PNG/p2_walk02.png"));
    framelist.push_back(LoadTexture("Player/p2_walk/PNG/p2_walk03.png"));
    framelist.push_back(LoadTexture("Player/p2_walk/PNG/p2_walk04.png"));
    framelist.push_back(LoadTexture("Player/p2_walk/PNG/p2_walk05.png"));
    framelist.push_back(LoadTexture("Player/p2_walk/PNG/p2_walk06.png"));
    framelist.push_back(LoadTexture("Player/p2_walk/PNG/p2_walk07.png"));
    framelist.push_back(LoadTexture("Player/p2_walk/PNG/p2_walk08.png"));
    framelist.push_back(LoadTexture("Player/p2_walk/PNG/p2_walk09.png"));
    framelist.push_back(LoadTexture("Player/p2_walk/PNG/p2_walk10.png"));
    framelist.push_back(LoadTexture("Player/p2_walk/PNG/p2_walk11.png"));
    target_time_frame=0.1f;
    elapsedtime=0.0f;
    currentframe=0;
}
void PlayerAnimation::Loadp3_walk()
{
    framelist.push_back(LoadTexture("Player/p3_walk/PNG/p3_walk01.png"));
    framelist.push_back(LoadTexture("Player/p3_walk/PNG/p3_walk02.png"));
    framelist.push_back(LoadTexture("Player/p3_walk/PNG/p3_walk03.png"));
    framelist.push_back(LoadTexture("Player/p3_walk/PNG/p3_walk04.png"));
    framelist.push_back(LoadTexture("Player/p3_walk/PNG/p3_walk05.png"));
    framelist.push_back(LoadTexture("Player/p3_walk/PNG/p3_walk06.png"));
    framelist.push_back(LoadTexture("Player/p3_walk/PNG/p3_walk07.png"));
    framelist.push_back(LoadTexture("Player/p3_walk/PNG/p3_walk08.png"));
    framelist.push_back(LoadTexture("Player/p3_walk/PNG/p3_walk09.png"));
    framelist.push_back(LoadTexture("Player/p3_walk/PNG/p3_walk10.png"));
    framelist.push_back(LoadTexture("Player/p3_walk/PNG/p3_walk11.png"));
    target_time_frame=0.05f;
    elapsedtime=0.0f;
    currentframe=0;
}
void PlayerAnimation::Loadp1_idle()
{
    target_time_frame=1.00f;
    elapsedtime=0.0f;
    currentframe=0;
    framelist.push_back(LoadTexture("Player/p1_stand.png"));
}
void PlayerAnimation::Loadp2_idle()
{
    target_time_frame=0.05f;
    elapsedtime=0.0f;
    currentframe=0;
    framelist.push_back(LoadTexture("Player/p2_stand.png"));
}
void PlayerAnimation::Loadp3_idle()
{
    target_time_frame=0.05f;
    elapsedtime=0.0f;
    currentframe=0;
    framelist.push_back(LoadTexture("Player/p3_stand.png"));
}
void PlayerAnimation::Unload()
{
    for(int i=0;i<framelist.size();i++)
    {
        UnloadTexture(framelist[i]);
    }
    framelist.clear();
    UnloadTexture(spritesheet);
}
PlayerAnimation::~PlayerAnimation()
{
    Unload();
}