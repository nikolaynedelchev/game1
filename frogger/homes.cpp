#include "all_modules.h"

namespace FroggerGame
{

void HomesModule::Init()
{
    for(size_t i = 0; i < 5; i++)
    {
        homes[i].homeRect = rss.homes[i];
        homes[i].isFull = false;
    }
}

void HomesModule::Update()
{
    if (frogger.state != FroggerState::Still)
    {
        return;
    }
    auto froggerSprite = frogger.GetCurrentSprite();
    for(auto& h : homes)
    {
        if (false == dd::sprite::collision(froggerSprite, "step", h.homeRect))
        {
            continue;
        }
        // frogger is at home
        if (h.isFull)
        {
            frogger.Hit();
            return;
        }
        h.isFull = true;
        frogger.AtHome();
        return;
    }
    if (frogger.position.y < UPPER_ROW_Y)
    {
        frogger.Hit();
    }
}

void HomesModule::Draw()
{
    for(auto& h : homes)
    {
        if (h.isFull)
        {
            auto s = rss.froggerUp[GND];
            s.position = h.homeRect.anchor_pos(dd::anchors::centered);
            s.size.x *= 1.3f;
            s.size.y *= 1.3f;
            s.anchor = dd::anchors::centered;
            s.draw();
        }
    }
}

HomesModule homes;
}

