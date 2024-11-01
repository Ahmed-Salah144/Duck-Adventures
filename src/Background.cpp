#include "Background.h"
void Background::LoadBackground3()
{
    layers.push_back(LoadTexture("game_background_3/layers/sky.png"));
    layers.push_back(LoadTexture("game_background_3/layers/clouds_1.png"));
    layers.push_back(LoadTexture("game_background_3/layers/rocks.png"));
    layers.push_back(LoadTexture("game_background_3/layers/clouds_2.png"));
    layers.push_back(LoadTexture("game_background_3/layers/ground_1.png"));
    layers.push_back(LoadTexture("game_background_3/layers/ground_2.png"));
    layers.push_back(LoadTexture("game_background_3/layers/ground_3.png"));
    layers.push_back(LoadTexture("game_background_3/layers/plant.png"));
    clouds.push_back(0);
    clouds.push_back(1);
    clouds.push_back(3);
    layerspeed=vector<float>(layers.size());
    layerspeed[0]=0;
    for(int i=1;i<layerspeed.size();i++)
    {
        layerspeed[i]=layerspeed[i-1]+BACKGROUND_SPEED*2;
    }
    layerx=vector<float>(layers.size());
}
void Background::LoadBackground2()
{
    layers.push_back(LoadTexture("game_background_2/layers/sky.png"));
    layers.push_back(LoadTexture("game_background_2/layers/clouds_1.png"));
    layers.push_back(LoadTexture("game_background_2/layers/rocks_3.png"));
    layers.push_back(LoadTexture("game_background_2/layers/clouds_2.png"));
    layers.push_back(LoadTexture("game_background_2/layers/rocks_2.png"));
    layers.push_back(LoadTexture("game_background_2/layers/clouds_3.png"));
    layers.push_back(LoadTexture("game_background_2/layers/birds.png"));
    layers.push_back(LoadTexture("game_background_2/layers/rocks_1.png"));
    layers.push_back(LoadTexture("game_background_2/layers/pines.png"));
    clouds.push_back(0);
    clouds.push_back(1);
    clouds.push_back(3);
    clouds.push_back(5);
    clouds.push_back(6);
    layerspeed=vector<float>(layers.size());
    layerspeed[0]=0;
    for(int i=1;i<layerspeed.size();i++)
    {
        layerspeed[i]=layerspeed[i-1]+BACKGROUND_SPEED*2;
    }
    layerx=vector<float>(layers.size());
}
void Background::LoadBackground1()
{
    layers.push_back(LoadTexture("game_background_1/layers/sky.png"));
    layers.push_back(LoadTexture("game_background_1/layers/clouds_1.png"));
    layers.push_back(LoadTexture("game_background_1/layers/clouds_2.png"));
    layers.push_back(LoadTexture("game_background_1/layers/rocks_1.png"));
    layers.push_back(LoadTexture("game_background_1/layers/clouds_3.png"));
    layers.push_back(LoadTexture("game_background_1/layers/rocks_2.png"));
    layers.push_back(LoadTexture("game_background_1/layers/clouds_4.png"));
    clouds.push_back(0);
    clouds.push_back(1);
    clouds.push_back(2);
    clouds.push_back(4);
    clouds.push_back(6);
    layerspeed=vector<float>(layers.size());
    layerspeed[0]=0;
    for(int i=1;i<layerspeed.size();i++)
    {
        layerspeed[i]=layerspeed[i-1]+BACKGROUND_SPEED*2;
    }
    layerx=vector<float>(layers.size());
}
void Background::LoadBackground4()
{
    layers.push_back(LoadTexture("game_background_4/layers/sky.png"));
    layers.push_back(LoadTexture("game_background_4/layers/clouds_1.png"));
    layers.push_back(LoadTexture("game_background_4/layers/rocks.png"));
    layers.push_back(LoadTexture("game_background_4/layers/clouds_2.png"));
    layers.push_back(LoadTexture("game_background_4/layers/ground_.png"));
    clouds.push_back(0);
    clouds.push_back(1);
    clouds.push_back(3);
    layerspeed=vector<float>(layers.size());
    layerspeed[0]=0;
    for(int i=1;i<layerspeed.size();i++)
    {
        layerspeed[i]=layerspeed[i-1]+BACKGROUND_SPEED*2;
    }
    layerx=vector<float>(layers.size());
}
void Background::LoadNextBackground()
{
    key++;
    key%=4;
    UnloadBackground();
    switch(key)
    {
        case 0:LoadBackground1();break;
        case 1:LoadBackground2();break;
        case 2:LoadBackground3();break;
        case 3:LoadBackground4();break;
    }
}
void Background::UpdateBackground(MyCamera * camptr)
{
    int cloudindex;
    int cloudsleft=clouds.size();

    if(prevcamlocation.x==camptr->camera.target.x)
        speed=0;
    else
        speed=BACKGROUND_SPEED;
    for(int i=0;i<layers.size();i++)
    {
        if(cloudsleft && i==clouds[cloudindex])
        {
            layerx[i]-=layerspeed[i]*GetFrameTime()*BACKGROUND_SPEED;
            cloudsleft--;
            cloudindex++;
        }
        else
            layerx[i]-=layerspeed[i]*GetFrameTime()*speed;
        if(layerx[i]<=-layers[i].width)
            layerx[i]=0;
        if(layerx[i]>=layers[i].width)
            layerx[i]=0;
    }
    for(int i=0;i<layers.size();i++)
    {
        DrawTextureEx(layers[i],Vector2{layerx[i]+(camptr->camera.target.x)-(camptr->camera.offset.x),0+(camptr->camera.target.y)-(camptr->camera.offset.y)},0.0f,1.0f,WHITE);
        DrawTextureEx(layers[i],Vector2{layerx[i]+layers[i].width+(camptr->camera.target.x)-(camptr->camera.offset.x),0+(camptr->camera.target.y)-(camptr->camera.offset.y)},0.0f,1.0f,WHITE);
    }
    prevcamlocation=camptr->camera.target;
}
void Background::UnloadBackground()
{
    for(int i=0;i<layers.size();i++)
    {
        UnloadTexture(layers[i]);
    }
    layerspeed.clear();
    layerx.clear();
    layers.clear();
    clouds.clear();
}
Background::~Background()
{
    UnloadBackground();
}