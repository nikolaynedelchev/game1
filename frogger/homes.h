#pragma once

#include "all_types.h"

namespace FroggerGame
{

struct HomesModule
{
    void Init();
    void Update();
    void Draw();

    FroggerHome homes[5];
};

extern HomesModule homes;
}
