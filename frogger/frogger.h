#pragma once

#include <dd.h>

namespace FroggerGame
{

enum class FroggerState
{
    Still,
    Jumping,
    AtHome,
    Dead
};

struct FroggerModule
{
    void Init();
    void Update();
    void Draw();

private:
    void UpdateStill();
    void UpdateJumping();
    void UpdateAtHome();
    void UpdateDead();

    void DrawStill();
    void DrawJumping();
    void DrawAtHome();
    void DrawDead();

    void StartJump(dd::direction);
    void JumpDone();

    dd::point position;
    dd::point jumpTarget;
    float jumpFramesRemaining = 0.0f;

    dd::direction direction = dd::direction::up;
    FroggerState state = FroggerState::Still;
    bool firstStateFrame = true;
};

extern FroggerModule frogger;
}
