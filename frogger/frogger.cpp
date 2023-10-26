#include "all_headers.h"

namespace FroggerGame
{

void FroggerModule::Init()
{
    position = {(rss.jumpingMinPos.x + rss.jumpingMaxPos.x) / 2.0f, rss.jumpingMaxPos.y};
    direction = dd::direction::up;
}

void FroggerModule::Update()
{
    auto oldState = state;

    if (state == FroggerState::Still)   UpdateStill();
    if (state == FroggerState::Jumping) UpdateJumping();
    if (state == FroggerState::AtHome)  UpdateAtHome();
    if (state == FroggerState::Dead)    UpdateDead();

    // check if new state is triggered
    if (oldState == state)
    {
        firstStateFrame = false;
    }
    else
    {
        firstStateFrame = true;
    }
}

void FroggerModule::Draw()
{
    if (state == FroggerState::Still)   DrawStill();
    if (state == FroggerState::Jumping) DrawJumping();
    if (state == FroggerState::AtHome)  DrawAtHome();
    if (state == FroggerState::Dead)    DrawDead();
}

void FroggerModule::UpdateStill()
{
    // update river object movements that affects frogger position
    // TODO:

    // update jump commands
    if (engine.key_pressed(dd::keys::UP))
    {
        StartJump(dd::direction::up);
    }
    if (engine.key_pressed(dd::keys::DOWN))
    {
        StartJump(dd::direction::down);
    }
    if (engine.key_pressed(dd::keys::LEFT))
    {
        StartJump(dd::direction::left);
    }
    if (engine.key_pressed(dd::keys::RIGHT))
    {
        StartJump(dd::direction::right);
    }
}

void FroggerModule::UpdateJumping()
{
    if (jumpFramesRemaining <= 0.0f)
    {
        JumpDone();
        return;
    }
    position += (jumpTarget - position) / jumpFramesRemaining;
    jumpFramesRemaining--;
}

void FroggerModule::UpdateAtHome()
{

}

void FroggerModule::UpdateDead()
{

}

void FroggerModule::DrawStill()
{
    if (direction == dd::direction::up)
    {
        rss.froggerUp[GND].draw_at(position, dd::anchors::centered);
    }
    if (direction == dd::direction::down)
    {
        rss.froggerDn[GND].draw_at(position, dd::anchors::centered);
    }
    if (direction == dd::direction::left)
    {
        rss.froggerLf[GND].draw_at(position, dd::anchors::centered);
    }
    if (direction == dd::direction::right)
    {
        rss.froggerRg[GND].draw_at(position, dd::anchors::centered);
    }
}

void FroggerModule::DrawJumping()
{
    if (direction == dd::direction::up)
    {
        rss.froggerUp[AIR].draw_at(position, dd::anchors::centered);
    }
    if (direction == dd::direction::down)
    {
        rss.froggerDn[AIR].draw_at(position, dd::anchors::centered);
    }
    if (direction == dd::direction::left)
    {
        rss.froggerLf[AIR].draw_at(position, dd::anchors::centered);
    }
    if (direction == dd::direction::right)
    {
        rss.froggerRg[AIR].draw_at(position, dd::anchors::centered);
    }

    if (firstStateFrame)
    {
        rss.jump.play();
    }
}

void FroggerModule::DrawAtHome()
{

}

void FroggerModule::DrawDead()
{

}

void FroggerModule::StartJump(dd::direction jumpDir)
{
    if (jumpDir == dd::direction::up)   jumpTarget = position - rss.vJumpSize;
    if (jumpDir == dd::direction::down) jumpTarget = position + rss.vJumpSize;
    if (jumpDir == dd::direction::left) jumpTarget = position - rss.hJumpSize;
    if (jumpDir == dd::direction::right)jumpTarget = position + rss.hJumpSize;

    if (jumpTarget.x > rss.jumpingMaxPos.x ||
        jumpTarget.x < rss.jumpingMinPos.x ||
        jumpTarget.y > rss.jumpingMaxPos.y ||
        jumpTarget.y < rss.jumpingMinPos.y)
    {
        jumpTarget = position;
    }

    direction = jumpDir;
    jumpFramesRemaining = rss.jumpFrames;
    state = FroggerState::Jumping;
}

void FroggerModule::JumpDone()
{
    position = jumpTarget;

    // TODO: Check for river collision.
    //       Kill the frog if so.

    state = FroggerState::Still;
}

FroggerModule frogger;
}

