#pragma once

#include <dd.h>

namespace FroggerGame
{

struct FroggerModule
{
    void Init();
    void Update();
    void Draw();

    float FroggerY() const;
    float FroggerX() const;
    dd::point FroggerTargetPos() const;

    dd::point froggerPosition;/* = {screenWidth / 2.0f, screenHeight / 2.0f}*/;
    dd::direction froggerDirection = dd::direction::up;
    bool isFroggerMoving = false;
    dd::point froggerDestination;
    float froggerSpeed = 2.0f; // pixels/frame
    float froggerJumpSize = 36.0f;
    float froggerJumpFramesLeft = 0.0f;

    int froggerRow = 0;
    int froggerColumn = 5;
    int froggerMaxRow = 12;
    int froggerMaxColumn = 10;
};

extern FroggerModule frogger;
}
