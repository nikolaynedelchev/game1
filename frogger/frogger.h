#pragma once

#include "all_types.h"

namespace FroggerGame
{

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

    void Die();
    void StartJump(dd::direction);
    void JumpDone();
    dd::sprite GetCurrentSprite() const;

    bool CheckForCollision();

    dd::point position;
    dd::point jumpTarget;
    float jumpFramesRemaining = 0.0f;

    dd::direction direction = dd::direction::up;
    FroggerState state = FroggerState::Still;
    bool firstStateFrame = true;
};

extern FroggerModule frogger;
}
