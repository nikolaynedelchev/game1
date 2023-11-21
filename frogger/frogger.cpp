#include "all_modules.h"

namespace FroggerGame
{

void FroggerModule::Init()
{
    RestartPosition();
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
    if (false == CheckAndUpdateStep())
    {
        if (CheckForWatter())
        {
            Drown();
            return;
        }
    }

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

    if (CheckForCollision())
    {
        Hit();
        return;
    }

    if (position.x < 5.0f || position.x > rss.screen.width - 5.0f)
    {
        Drown();
        return;
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

    if (CheckForCollision())
    {
        Hit();
        return;
    }
}

void FroggerModule::UpdateAtHome()
{
    if (rss.extraLife.is_playing())
    {
        return;
    }
    RestartPosition();
}

void FroggerModule::UpdateDead()
{
    rss.landDeathAnim.update();
    if (rss.landDeathAnim.finished())
    {
        rss.landDeathAnim.visible = false;
        position = {(rss.jumpingMinPos.x + rss.jumpingMaxPos.x) / 2.0f, rss.jumpingMaxPos.y};
        direction = dd::direction::up;
        state = FroggerState::Still;
    }
}

void FroggerModule::DrawStill()
{
    GetCurrentSprite().draw();
}

void FroggerModule::DrawJumping()
{
    GetCurrentSprite().draw();
}

void FroggerModule::DrawAtHome()
{

}

void FroggerModule::DrawDead()
{
    rss.landDeathAnim.draw();
}

void FroggerModule::Hit()
{
    rss.hit.play();
    state = FroggerState::Dead;
    rss.landDeathAnim.visible = true;
    rss.landDeathAnim.position = jumpTarget;
    rss.landDeathAnim.play();
}

void FroggerModule::Drown()
{
    rss.drown.play();
    state = FroggerState::Dead;
    rss.landDeathAnim.visible = true;
    rss.landDeathAnim.position = jumpTarget;
    rss.landDeathAnim.play();
}

void FroggerModule::AtHome()
{
    state = FroggerState::AtHome;
    rss.extraLife.play();
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
    rss.jump.play();
}

void FroggerModule::JumpDone()
{
    position = jumpTarget;

    // TODO: Check for river collision.
    //       Kill the frog if so.

    state = FroggerState::Still;
}

dd::sprite FroggerModule::GetCurrentSprite() const
{
    dd::sprite s;
    if (state == FroggerState::Still)
    {
        if (direction == dd::direction::up)
        {
            s = rss.froggerUp[GND];
        }
        if (direction == dd::direction::down)
        {
            s = rss.froggerDn[GND];
        }
        if (direction == dd::direction::left)
        {
            s = rss.froggerLf[GND];
        }
        if (direction == dd::direction::right)
        {
            s = rss.froggerRg[GND];
        }
    }
    else if (state == FroggerState::Jumping)
    {
        if (direction == dd::direction::up)
        {
            s = rss.froggerUp[AIR];
        }
        if (direction == dd::direction::down)
        {
            s = rss.froggerDn[AIR];
        }
        if (direction == dd::direction::left)
        {
            s = rss.froggerLf[AIR];
        }
        if (direction == dd::direction::right)
        {
            s = rss.froggerRg[AIR];
        }
    }
    s.position = position;
    s.anchor = dd::anchors::centered;
    return s;
}

void FroggerModule::RestartPosition()
{
    position = {(rss.jumpingMinPos.x + rss.jumpingMaxPos.x) / 2.0f, rss.jumpingMaxPos.y};
    direction = dd::direction::up;
    state = FroggerState::Still;
}

bool FroggerModule::CheckForCollision()
{
    auto froggerSprite = GetCurrentSprite();
    for(auto& obj : objects.objects)
    {
        if (obj.isActive == false) continue;

        if (dd::anim::collision(obj.animation, "hit", froggerSprite, "hit"))
        {
            return true;
        }
    }
    return false;
}

bool FroggerModule::CheckForWatter()
{
    if (position.y < MID_LAND_Y && position.y > UPPER_ROW_Y)
    {
        return true;
    }
    return false;
}

bool FroggerModule::CheckAndUpdateStep()
{
    if (state != FroggerState::Still)
        return false;

    auto froggerSprite = GetCurrentSprite();
    for(auto& obj : objects.objects)
    {
        if (obj.isActive == false) continue;

        if (dd::anim::collision(obj.animation, "step", froggerSprite, "step"))
        {
            position += obj.velocity;
            return true;
        }
    }
    return false;
}

FroggerModule frogger;
}

