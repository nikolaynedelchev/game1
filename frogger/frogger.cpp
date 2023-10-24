#include "all_headers.h"

namespace FroggerGame
{

void FroggerModule::Init()
{
    froggerPosition = FroggerTargetPos();
}

void FroggerModule::Update()
{
    if (isFroggerMoving)
    {
        if (froggerJumpFramesLeft == 0.0f)
        {
            froggerPosition = froggerDestination;
            isFroggerMoving = false;
            return;
        }

        if (froggerDirection == dd::direction::up)
        {
            if (froggerPosition.y > froggerDestination.y)
                froggerPosition.y -= froggerSpeed;
        }
        if (froggerDirection == dd::direction::down)
        {
            if (froggerPosition.y < froggerDestination.y)
                froggerPosition.y += froggerSpeed;
        }
        if (froggerDirection == dd::direction::left)
        {
            if (froggerPosition.x > froggerDestination.x)
                froggerPosition.x -= froggerSpeed;
        }
        if (froggerDirection == dd::direction::right)
        {
            if (froggerPosition.x < froggerDestination.x)
                froggerPosition.x += froggerSpeed;
        }

        froggerJumpFramesLeft--;

        return;
    }

    if (engine.key_pressed(dd::keys::UP))
    {
        isFroggerMoving = true;
        froggerJumpFramesLeft = froggerJumpSize / froggerSpeed;
        froggerDestination = froggerPosition;
        if (froggerRow < froggerMaxRow)
        {
            froggerRow++;
        }
        froggerDirection = dd::direction::up;
    }
    if (engine.key_pressed(dd::keys::DOWN))
    {
        isFroggerMoving = true;
        froggerJumpFramesLeft = froggerJumpSize / froggerSpeed;
        froggerDestination = froggerPosition;
        if (froggerRow > 0)
        {
            froggerRow--;
        }
        froggerDirection = dd::direction::down;
    }
    if (engine.key_pressed(dd::keys::LEFT))
    {
        isFroggerMoving = true;
        froggerJumpFramesLeft = froggerJumpSize / froggerSpeed;
        froggerDestination = froggerPosition;
        if (froggerColumn > 0)
        {
            froggerColumn--;
        }
        froggerDirection = dd::direction::left;
    }
    if (engine.key_pressed(dd::keys::RIGHT))
    {
        isFroggerMoving = true;
        froggerJumpFramesLeft = froggerJumpSize / froggerSpeed;
        froggerDestination = froggerPosition;
        if (froggerColumn < froggerMaxColumn)
        {
            froggerColumn++;
        }
        froggerDirection = dd::direction::right;
    }
    froggerDestination = FroggerTargetPos();
}

void FroggerModule::Draw()
{
    dd::sprite s;
    if (isFroggerMoving)
    {
        if (froggerDirection == dd::direction::up)
        {
            s = Rss::GetSprite("frogger_up_air");
        }
        if (froggerDirection == dd::direction::down)
        {
            s = Rss::GetSprite("frogger_down_air");
        }
        if (froggerDirection == dd::direction::left)
        {
            s = Rss::GetSprite("frogger_left_air");
        }
        if (froggerDirection == dd::direction::right)
        {
            s = Rss::GetSprite("frogger_right_air");
        }
    }
    else
    {
        if (froggerDirection == dd::direction::up)
        {
            s = Rss::GetSprite("frogger_up_ground");
        }
        if (froggerDirection == dd::direction::down)
        {
            s = Rss::GetSprite("frogger_down_ground");
        }
        if (froggerDirection == dd::direction::left)
        {
            s = Rss::GetSprite("frogger_left_ground");
        }
        if (froggerDirection == dd::direction::right)
        {
            s = Rss::GetSprite("frogger_right_ground");
        }
    }
    s.change_anchor(dd::anchors::centered);
    s.position = froggerPosition;
    s.draw();
}

float FroggerModule::FroggerY() const
{
    return LOW_LAND_Y + ROW_H / 2.0f - float(froggerRow) * ROW_H;
}

float FroggerModule::FroggerX() const
{
    return froggerColumn * froggerJumpSize + froggerJumpSize / 2.0f;
}

dd::point FroggerModule::FroggerTargetPos() const
{
    return {FroggerX(), FroggerY()};
}

FroggerModule frogger;
}

