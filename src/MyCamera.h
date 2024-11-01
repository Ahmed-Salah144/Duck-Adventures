#pragma once
#include"global.h"
#include "raylib.h"

class MyCamera {
public:
    Camera2D camera;
    Vector2 minpos;
    Vector2 maxpos;

    MyCamera(float zoom = 1.0f);

    void Follow(Vector2);

    void setPosition(Vector2);

    void setOffset(Vector2);

    void setZoom(float newZoom);

    void beginMode();

    void endMode();
};