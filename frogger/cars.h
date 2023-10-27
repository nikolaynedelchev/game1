#pragma once

#include "all_types.h"

namespace FroggerGame
{

struct CarsModule
{
    void Init();
    void Update();
    void Draw();

    void UpdateObjects();
    void UpdateEmitters();
    void EmitObject(ObjectEmitter& emitter);

    LevelEmitters levelEmitters;
    GameObject objects[64];
};

extern CarsModule cars;
}
