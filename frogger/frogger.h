#pragma once

#include "all_types.h"

namespace FroggerGame
{

struct FroggerModule
{
    void Init();
    void Update();
    void Draw();

    void UpdateStill();
    void UpdateJumping();
    void UpdateAtHome();
    void UpdateDead();

    void DrawStill();
    void DrawJumping();
    void DrawAtHome();
    void DrawDead();

    void Hit();
    void Drown();

    void AtHome();
    void StartJump(dd::direction);
    void JumpDone();
    dd::sprite GetCurrentSprite() const;
    void RestartPosition();

    bool CheckForCollision();
    bool CheckForWatter();

    bool CheckAndUpdateStep();

    dd::point position;
    dd::point jumpTarget;
    float jumpFramesRemaining = 0.0f;

    dd::direction direction = dd::direction::up;
    FroggerState state = FroggerState::Still;
    bool firstStateFrame = true;
};

extern FroggerModule frogger;
}
