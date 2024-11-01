#pragma once
#include"global.h"
#include"MyCamera.h"
using namespace std;
class Background
{
    public:
    vector<Texture2D> layers;
    vector<float> layerx;
    vector<float> layerspeed;
    vector<int> clouds;
    float speed = BACKGROUND_SPEED;
    Vector2 prevcamlocation={0,0};
    int key=0;
    void LoadNextBackground();
    void LoadBackground3();
    void LoadBackground1();
    void LoadBackground2();
    void LoadBackground4();
    void UpdateBackground(MyCamera* camptr);
    void UnloadBackground();
    ~Background();
    
};