#include"MyCamera.h"

    MyCamera::MyCamera(float zoom) {
        camera.target = {0.0f, 0.0f};
        camera.offset = {0.0f, 0.0f};  // Will set this in setPosition
        camera.rotation = 0.0f;
        camera.zoom = zoom;
        minpos={SCREEN_WIDTH/2,SCREEN_HEIGHT/2};
        maxpos={(WORLD_WIDTH_TILES-SCREEN_WIDTH_TILES/2.0f-1.0f)*TILE_SIZE,(WORLD_HEIGHT_TILES-SCREEN_HEIGHT_TILES/2.0f-1.0f)*TILE_SIZE};
    }
    void MyCamera::Follow(Vector2 pos)
    {   
        camera.target.y=max(minpos.y,min(maxpos.y,pos.y));
        camera.target.x=max(minpos.x,min(maxpos.x,pos.x));

    }
    void MyCamera::setPosition(Vector2 pos) {
        camera.target.x = pos.x;
        camera.target.y = pos.y;
    }
    void MyCamera::setOffset(Vector2 pos) {
        camera.offset = pos; // Center the camera
    }
    
    void MyCamera::setZoom(float newZoom) {
        camera.zoom = newZoom;
    }

    void MyCamera::beginMode() {
        BeginMode2D(camera);
    }

    void MyCamera::endMode() {
        EndMode2D();
    }