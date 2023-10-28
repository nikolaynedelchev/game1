#pragma once
#include <dd.h>

namespace FroggerGame
{

struct GameObject
{
    bool isActive = false;
    dd::anim animation;
    dd::vec velocity;
};

struct ObjectEmitter
{
    bool isActive = false;
    GameObject objTemplate;
    int emitDistribution[8]; // frames to count before sponing the next object;
    size_t distIdx = 0;
    int frameCounter = 0;
    std::string name;
};

struct LevelEmitters
{
    ObjectEmitter emitters[32];
};

enum class FroggerState
{
    Still,
    Jumping,
    AtHome,
    Dead
};

struct FroggerHome
{
    dd::rect homeRect;
    bool isFull = false;
};


}
