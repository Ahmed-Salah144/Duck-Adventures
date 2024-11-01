#include"Player.h"
Player::Player()
{
    pos.x=PLAYER_INITIAL_X;
    pos.y=PLAYER_INITIAL_Y;
    prevpos=pos;
    tileposrow=pos.y/TILE_SIZE;
    tileposcol=pos.x/TILE_SIZE;
    speed_x=PLAYER_SPEED;
    speed_y=0;
    Hitbox_Rec.width=PLAYER_HITBOX_WIDTH;
    Hitbox_Rec.height=PLAYER_HITBOX_HEIGHT;
    Hitbox_Circ.r=PLAYER_HITBOX_RADIUS;
    dest.width=PLAYER_DEST_WIDTH;
    dest.height=PLAYER_DEST_HEIGHT;
    UpdateHitbox();
    Updatedest();
    walk.Load64fast(WALK);
    idle.Load64slow(IDLE);
    fall.Load64slow(FALL);
    land.Load64slow(LAND);
    jump.Load64slow(JUMP);
    crouch.Load64slow(CROUCH);
    crawl.Load64fast(CRAWL);
    punch.Load64fast(RIGHT_LEFT_COMBO);
    direction=1;
    on_ground=false;
    landing=false;
    jumping=false;
    locktime=0.0f;
}
void Player::UpdateData(World* w)
{
    float dt=GetFrameTime();
    world=w;
    if(landing && ! land.isOver())
    {
        animations.push(LAND);
        return;
    }
    else if(landing)
    {
        landing=false;
    }
    CheckBelow();
    if((IsKeyReleased(MOVE_UP)||IsKeyPressed(MOVE_UP))&& on_ground&& !IsKeyDown(MOVE_DOWN))
    {

        speed_y-=PLAYER_JUMP;
        on_ground=false;
        jumping=true;
        jump.Reset();
    }
    if(IsKeyDown(MOVE_RIGHT)&&!IsKeyDown(MOVE_LEFT))
    {
        pos.x+=speed_x*dt;
        if(torsocollision())
            pos.x-=speed_x*dt;
        if(on_ground && IsKeyDown(MOVE_DOWN))
        { 
            animations.push(CRAWL);
        }
        else if(on_ground)
        {
            animations.push(WALK);
        }
        direction=1;
    }
    if(IsKeyDown(MOVE_LEFT)&&!IsKeyDown(MOVE_RIGHT))
    {
        pos.x-=speed_x*dt;
        if(torsocollision())
            pos.x+=speed_x*dt;
        if(on_ground && IsKeyDown(MOVE_DOWN))
        { 
            animations.push(CRAWL);
        }
        else if(on_ground)
        {
            animations.push(WALK);
        }
        direction=-1;
    }
    Unclipfeet();
    if(!IsInsideWorld(pos))
    {
        Reset();
    }
    if(!on_ground)
    {
        speed_y+= GRAVITY *dt;
        pos.y+=speed_y*dt;
        if(torsocollision() && !footcollision())
        {
            pos.y-=speed_y*dt;
            speed_y=0;
        }
        if(footcollision() && !torsocollision())
        {
            Unclipfeet();
            on_ground=true;
            jumping=false;
            if(speed_y > PLAYER_JUMP*1.25)
            {
                landing=true;
                land.Reset();
            }
        }
        if(footcollision() && torsocollision())
        {
            pos.y-=speed_y*dt;
            speed_y=0;
        }
        if(!on_ground && ! jumping ) 
            animations.push(FALL);
    }
    if(jumping && !jump.isOver())
    {
        animations.push(JUMP);
    }
    else if(jumping)
        jumping = false;
    if(! footcollision() && ! torsocollision())
    {
        prevpos=pos;
    }
    else
    {
        pos=prevpos;
        UpdatePositionData();
    }
    if(IsKeyDown(PUNCH))
    {
        if(!animations.empty())
            animations.pop();
        animations.push(RIGHT_LEFT_COMBO);
    }
    if(animations.empty())
    {
        if(IsKeyDown(MOVE_DOWN))
            animations.push(CROUCH);
        else
            animations.push(IDLE);
    }

}
void Player::DrawData()
{
    //DrawRectangleLinesEx(dest,1.0f,ORANGE);
    //DrawRectangleRec(Hitbox_Rec,ORANGE);
    //DrawCircle(Hitbox_Circ.x,Hitbox_Circ.y,Hitbox_Circ.r,ORANGE);
    while(!animations.empty())
    {
        switch(animations.front())
        {
            case IDLE:
                //DrawRectangleRec(Hitbox_Rec,ORANGE);
                //DrawCircle(Hitbox_Circ.x,Hitbox_Circ.y,Hitbox_Circ.r,ORANGE);
                idle.animate64(dest,direction);break;
            case WALK:walk.animate64(dest,direction);break;
            case FALL:fall.animate64(dest,direction);break;
            case LAND:land.animate64(dest,direction);break;
            case JUMP:jump.animate64(dest,direction);break;
            case CROUCH:crouch.animate64(dest,direction);break;
            case CRAWL:crawl.animate64(dest,direction);break;
            case RIGHT_LEFT_COMBO:punch.animate64(dest,direction);break;

            default:
            {
                DrawRectangleRec(Hitbox_Rec,ORANGE);
                DrawCircle(Hitbox_Circ.x,Hitbox_Circ.y,Hitbox_Circ.r,ORANGE);
                idle.animate64(dest,direction);
            }
        }
        animations.pop();
    }
}
void Player::UpdateHitbox()
{
    Hitbox_Rec.x= pos.x - PLAYER_HITBOX_WIDTH/2;
    Hitbox_Rec.y= pos.y;
    Hitbox_Circ.x=pos.x;
    Hitbox_Circ.y=pos.y + PLAYER_HITBOX_HEIGHT*1.1;
    tileposcol=pos.x/TILE_SIZE;
    tileposrow=pos.y/TILE_SIZE;
}
void Player::Updatedest()
{
    dest.x=pos.x- PLAYER_DEST_WIDTH/2;
    dest.y=pos.y - PLAYER_DEST_HEIGHT/2;
}
void Player::UpdateTilepos()
{
    tileposcol=max(tileposcol,COLLISION_RANGE);
    tileposrow=max(tileposrow,COLLISION_RANGE);
    tileposrow=min(tileposrow,WORLD_HEIGHT_TILES-COLLISION_RANGE-1);
    tileposcol=min(tileposcol,WORLD_WIDTH_TILES-COLLISION_RANGE-1);
}
int Player::footcollision()
{
    UpdatePositionData();
    for(int i=tileposrow-COLLISION_RANGE;i<tileposrow+COLLISION_RANGE+1;i++)
        for(int j=tileposcol-COLLISION_RANGE;j<tileposcol+COLLISION_RANGE+1;j++)
        {
            int texid=world->tile_grid[i][j].texture_ID; 
            if(!IsTileSafe(texid) && CheckCollisionCircleRec({Hitbox_Circ.x,Hitbox_Circ.y+2},Hitbox_Circ.r,world->tile_grid[i][j].Hitbox))
                return texid;
        }
    return 0;

}
int Player::torsocollision()
{
    UpdatePositionData();
    for(int i=tileposrow-COLLISION_RANGE;i<tileposrow+COLLISION_RANGE+1;i++)
        for(int j=tileposcol-COLLISION_RANGE;j<tileposcol+COLLISION_RANGE+1;j++)
        {
            int texid=world->tile_grid[i][j].texture_ID; 
            if(!IsTileSafe(texid) && CheckCollisionRecs(Hitbox_Rec,world->tile_grid[i][j].Hitbox))
                return texid;
        }
    return 0;
}
int Player::headcollision()
{
    UpdatePositionData();
    Vector2 Headleft={Hitbox_Rec.x-5,Hitbox_Rec.y-5};
    Vector2 Headright={Hitbox_Rec.x+5 +Hitbox_Rec.width,Hitbox_Rec.y-5};
    for(int i=tileposrow-COLLISION_RANGE;i<tileposrow+COLLISION_RANGE+1;i++)
        for(int j=tileposcol-COLLISION_RANGE;j<tileposcol+COLLISION_RANGE+1;j++)
        {
            int texid=world->tile_grid[i][j].texture_ID; 
            if(!IsTileSafe(texid) && CheckCollisionPointRec(Headleft,world->tile_grid[i][j].Hitbox))
                return texid;
        }
    for(int i=tileposrow-COLLISION_RANGE;i<tileposrow+COLLISION_RANGE+1;i++)
        for(int j=tileposcol-COLLISION_RANGE;j<tileposcol+COLLISION_RANGE+1;j++)
        {
            int texid=world->tile_grid[i][j].texture_ID; 
            if(!IsTileSafe(texid) && CheckCollisionPointRec(Headright,world->tile_grid[i][j].Hitbox))
                return texid;
        }
    return 0;
}
int Player::anycollision()
{
    return max(max(headcollision(),torsocollision()),footcollision());
}
void Player::Unclipfeet()
{
    
    while(footcollision())
    {
        pos.y-=1;
    }
    UpdatePositionData();
}
void Player::Uncliphead()
{
    while(headcollision())
    {
        pos.y+=3;
    }
    pos.y+=3;
}
void Player::Uncliptorso()
{  
    while(torsocollision())
    {
        while(footcollision())
        {
            Unclipfeet();
            //cout<<"FEET"<<footcollision()<<endl;
        }
        while(headcollision())
        {
            pos.y+=1;
            //cout<<"HEAD"<<headcollision()<<endl;
        }
        while(leftcollision())
        {
            pos.x+=1;
            //cout<<"LEFT"<<leftcollision()<<endl;
        }
        while(rightcollision())
        {
            pos.x-=1;
            //cout<<"RIGHT"<<rightcollision()<<endl;
        }
        pos.y-=1;
        //cout<<"TORSO"<<torsocollision()<<endl;
        if(torsocollision())
        {
            pos.y-=Hitbox_Rec.height;
        }
    }
}
int Player::leftcollision()
{
    UpdatePositionData();
    Vector2 left1={Hitbox_Rec.x-5,Hitbox_Rec.y+Hitbox_Rec.height/4};
    Vector2 left2={Hitbox_Rec.x-5,Hitbox_Rec.y+Hitbox_Rec.y+Hitbox_Rec.height-5};
    for(int i=tileposrow-COLLISION_RANGE;i<tileposrow+COLLISION_RANGE+1;i++)
        for(int j=tileposcol-COLLISION_RANGE;j<tileposcol+COLLISION_RANGE+1;j++)
        {
            int texid=world->tile_grid[i][j].texture_ID; 
            if(!IsTileSafe(texid) && CheckCollisionPointRec(left1,world->tile_grid[i][j].Hitbox))
                return texid;
        }
    for(int i=tileposrow-COLLISION_RANGE;i<tileposrow+COLLISION_RANGE+1;i++)
        for(int j=tileposcol-COLLISION_RANGE;j<tileposcol+COLLISION_RANGE+1;j++)
        {
            int texid=world->tile_grid[i][j].texture_ID; 
            if(!IsTileSafe(texid) && CheckCollisionPointRec(left2,world->tile_grid[i][j].Hitbox))
                return texid;
        }
    return 0;
}
int Player::rightcollision()
{
    UpdatePositionData();
    Vector2 right1={Hitbox_Rec.x+Hitbox_Rec.y+Hitbox_Rec.height/4};
    Vector2 right2={Hitbox_Rec.x+Hitbox_Rec.width+5,Hitbox_Rec.y+Hitbox_Rec.height-5};
    for(int i=tileposrow-COLLISION_RANGE;i<tileposrow+COLLISION_RANGE+1;i++)
        for(int j=tileposcol-COLLISION_RANGE;j<tileposcol+COLLISION_RANGE+1;j++)
        {
            int texid=world->tile_grid[i][j].texture_ID; 
            if(!IsTileSafe(texid) && CheckCollisionPointRec(right1,world->tile_grid[i][j].Hitbox))
                return texid;
        }
    for(int i=tileposrow-COLLISION_RANGE;i<tileposrow+COLLISION_RANGE+1;i++)
        for(int j=tileposcol-COLLISION_RANGE;j<tileposcol+COLLISION_RANGE+1;j++)
        {
            int texid=world->tile_grid[i][j].texture_ID; 
            if(!IsTileSafe(texid) && CheckCollisionPointRec(right2,world->tile_grid[i][j].Hitbox))
                return texid;
        }
    return 0;
}
void Player::Reset()
{
    pos.x=PLAYER_INITIAL_X;
    pos.y=PLAYER_INITIAL_Y;
    tileposrow=pos.y/TILE_SIZE;
    tileposcol=pos.x/TILE_SIZE;
    speed_x=PLAYER_SPEED;
    speed_y=0;
    Hitbox_Rec.width=PLAYER_HITBOX_WIDTH;
    Hitbox_Rec.height=PLAYER_HITBOX_HEIGHT;
    Hitbox_Circ.r=PLAYER_HITBOX_RADIUS;
    dest.width=PLAYER_DEST_WIDTH;
    dest.height=PLAYER_DEST_HEIGHT;
    UpdateHitbox();
    Updatedest();
}
void Player::UpdatePositionData()
{
    UpdateHitbox();
    Updatedest();
    UpdateTilepos();
}
void Player::CheckBelow()
{
    pos.y+=3;
    int tileid=max(footcollision(),torsocollision());
    if(tileid==0)
    {
        on_ground=false;
    }
    else if(IsTileHarmful(tileid))
    {
        Reset();
    }
    else
    {
        speed_y=min(speed_y,0.0f);
        if (speed_y==0.0f)
        {
            on_ground=true;
            jumping=false;
        }
    }
    pos.y-=3;
    UpdatePositionData();
}
    Player::~Player()
    {
        walk.Unload();
        idle.Unload();
        jump.Unload();
        fall.Unload();
        land.Unload();
    }

