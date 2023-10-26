#pragma once

#include <dd.h>

namespace FroggerGame
{

enum class CarType
{

};

struct CarsModule
{
    void Init();
    void Update();
    void Draw();
};

struct CarLane
{

};

extern CarsModule cars;
}
