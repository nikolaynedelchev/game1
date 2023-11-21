#include "all_modules.h"

namespace FroggerGame
{

void SnakesModule::Init()
{
    for(auto& o : objects) o.isActive = false;
    levelEmitters = levels.GetLevelObjectEmitter(1);
    for(int i = 0; i < 1400; i++) Update();
}

void SnakesModule::Update()
{
    UpdateObjects();
    UpdateEmitters();
}

void SnakesModule::Draw()
{
    for(auto& obj : objects)
    {
        if (obj.isActive == false) continue;
        if (obj.name == "turtle")
        {
            int aaa = 34;
            (void)aaa;
        }
        obj.animation.draw();
    }
}

void SnakesModule::UpdateObjects()
{
    for(auto& obj : objects)
    {
        if (obj.isActive == false) continue;
        obj.animation.position += obj.velocity;
        obj.animation.update();

        if (obj.animation.position.x > OFFSCR_MAX ||
            obj.animation.position.x < OFFSCR_MIN)
        {
            obj.isActive = false;
            continue;
        }
    }
}

void SnakesModule::UpdateEmitters()
{
    for(auto& emitter : levelEmitters.emitters)
    {
        if (emitter.isActive == false) continue;
        if (emitter.frameCounter >= emitter.emitDistribution[emitter.distIdx])
        {
            EmitObject(emitter);
        }
        else
        {
            emitter.frameCounter++;
        }
    }
}

void SnakesModule::EmitObject(ObjectEmitter &emitter)
{
    for(auto& object : objects)
    {
        if (object.isActive == true) continue;
        object = emitter.objTemplate;
        object.animation.play();
        emitter.frameCounter = 0;
        emitter.distIdx++;
        if (emitter.emitDistribution[emitter.distIdx] == 0)
        {
            emitter.distIdx = 0;
        }
        return;
    }
}

SnakesModule snakes;
}

