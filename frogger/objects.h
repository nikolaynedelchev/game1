﻿#pragma once

#include "all_types.h"

namespace FroggerGame
{

struct ObjectsModule
{
    void Init();
    void Update();
    void Draw();

    void UpdateObjects();
    void UpdateEmitters();
    void EmitObject(ObjectEmitter& emitter);

    LevelEmitters levelEmitters;
    GameObject objects[128];
};

extern ObjectsModule objects;
}
