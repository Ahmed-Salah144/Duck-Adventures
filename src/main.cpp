#include "Player.h"
#include "global.h"
#include "World.h"
#include "MyCamera.h"
#include "Background.h"
#include "Button.h"
#include <myinclude/safeSave.h>
using namespace std;
int main()
{
    InitWindow(SCREEN_WIDTH,SCREEN_HEIGHT,"GAME");
    LoadTileMapper();
    PrepareAnimationMap();
    Player player;
    World world;
    MyCamera camera;
    Background Bg;
    Bg.LoadBackground2();
    world.LoadWorld1();
    camera.setPosition(player.pos);
    camera.setOffset({SCREEN_WIDTH/2,SCREEN_HEIGHT/2});
    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        player.UpdateData(&world);
        camera.Follow(player.pos);




        BeginDrawing();
        //BEFORE 2DMODE STUFF MOVE WITH PLAYER(use screen coordinates)
        //AFTER 2DMODE STUFF IS LEFT BEHIND WHEN PLAYER MOVES(use world coordinates)


        ClearBackground(BLACK);
        //Bg.UpdateBackground(&camera);
        //DrawText((to_string((int)player.pos.x)+"   "+to_string((int)player.pos.y)).c_str(),0,0,100,WHITE);



        camera.beginMode();
        Bg.UpdateBackground(&camera);
        world.DrawWorld(player.pos);
        player.DrawData(); 

        camera.endMode();
        EndDrawing();
    }
    UnloadTileMapper();
    CloseWindow();
    return 0;
}