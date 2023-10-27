#include "all_modules.h"

namespace FroggerGame
{

void CarsModule::Init()
{
    for(auto& o : objects) o.isActive = false;
    levelEmitters = levels.GetLevelObjectEmitter(1);
}

void CarsModule::Update()
{
    UpdateObjects();
    UpdateEmitters();
}

void CarsModule::Draw()
{
    for(auto& obj : objects)
    {
        if (obj.isActive == false) continue;
        obj.animation.draw();
    }
}

void CarsModule::UpdateObjects()
{
    for(auto& obj : objects)
    {
        if (obj.isActive == false) continue;
        obj.animation.position += obj.velocity;
        obj.animation.update();

        if (false == dd::rect::collision(obj.animation.rect(), rss.screen))
        {
            obj.isActive = false;
            continue;
        }
    }
}

void CarsModule::UpdateEmitters()
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

void CarsModule::EmitObject(ObjectEmitter &emitter)
{
    for(size_t i = 0; i < 32; i++)
    {
        if (objects[i].isActive == true) continue;
        objects[i] = emitter.objTemplate;
        objects[i].animation.play();
        emitter.frameCounter = 0;
        emitter.distIdx++;
        if (emitter.emitDistribution[emitter.distIdx] == 0)
        {
            emitter.distIdx = 0;
        }
        return;
    }
}

CarsModule cars;
}

