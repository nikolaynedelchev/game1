#pragma once

#include "all_types.h"

namespace FroggerGame
{

struct Level
{

};

struct LevelsModule
{
    void Init();
    LevelEmitters GetLevelObjectEmitter(int level) const;
};

extern LevelsModule levels;
}
