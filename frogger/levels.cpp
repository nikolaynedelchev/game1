#include "all_modules.h"

namespace FroggerGame
{

void LevelsModule::Init()
{

}

LevelEmitters GetTestLevelObjectEmitter()
{
    LevelEmitters levelEmitters;
    for(auto& e : levelEmitters.emitters) e.isActive = false;

    // row 1 (fast left car)
    levelEmitters.emitters[0].isActive = true;
    levelEmitters.emitters[0].distIdx = 0;
    levelEmitters.emitters[0].frameCounter = 810;
    levelEmitters.emitters[0].objTemplate.animation = rss.fastLeftCarAnim;
    levelEmitters.emitters[0].objTemplate.animation.position = {rss.screen.width, CARS_1_Y};
    levelEmitters.emitters[0].objTemplate.isActive = true;
    levelEmitters.emitters[0].objTemplate.velocity = {-0.3f, 0.0f};
    levelEmitters.emitters[0].emitDistribution[0] = 1010;
    levelEmitters.emitters[0].emitDistribution[1] = 0; // end

    return levelEmitters;
}


LevelEmitters LevelsModule::GetLevelObjectEmitter(int level) const
{
    (void)level;
    //return GetTestLevelObjectEmitter();
    LevelEmitters levelEmitters;
    for(auto& e : levelEmitters.emitters) e.isActive = false;

    // row 1 (fast left car)
    levelEmitters.emitters[0].isActive = true;
    levelEmitters.emitters[0].distIdx = 0;
    levelEmitters.emitters[0].frameCounter = 190;
    levelEmitters.emitters[0].objTemplate.animation = rss.fastLeftCarAnim;
    levelEmitters.emitters[0].objTemplate.animation.position = {rss.screen.width, CARS_1_Y};
    levelEmitters.emitters[0].objTemplate.isActive = true;
    levelEmitters.emitters[0].objTemplate.velocity = {-0.7f, 0.0f};
    levelEmitters.emitters[0].emitDistribution[0] = 210;
    levelEmitters.emitters[0].emitDistribution[1] = 80;
    levelEmitters.emitters[0].emitDistribution[2] = 150;
    levelEmitters.emitters[0].emitDistribution[3] = 80;
    levelEmitters.emitters[0].emitDistribution[4] = 0; // end

    // row 2 (tractor)
    levelEmitters.emitters[1].isActive = true;
    levelEmitters.emitters[1].distIdx = 0;
    levelEmitters.emitters[1].frameCounter = 240;
    levelEmitters.emitters[1].objTemplate.animation = rss.tractorAnim;
    levelEmitters.emitters[1].objTemplate.animation.position = {0, CARS_2_Y};
    levelEmitters.emitters[1].objTemplate.isActive = true;
    levelEmitters.emitters[1].objTemplate.velocity = {0.4f, 0.0f};
    levelEmitters.emitters[1].emitDistribution[0] = 250;
    levelEmitters.emitters[1].emitDistribution[1] = 0; // end

    // row 3 (slow left car)
    levelEmitters.emitters[2].isActive = true;
    levelEmitters.emitters[2].distIdx = 0;
    levelEmitters.emitters[2].frameCounter = 100;
    levelEmitters.emitters[2].objTemplate.animation = rss.slowCarAnim;
    levelEmitters.emitters[2].objTemplate.animation.position = {rss.screen.width, CARS_3_Y};
    levelEmitters.emitters[2].objTemplate.isActive = true;
    levelEmitters.emitters[2].objTemplate.velocity = {-0.6f, 0.0f};
    levelEmitters.emitters[2].emitDistribution[0] = 160;
    levelEmitters.emitters[2].emitDistribution[1] = 100;
    levelEmitters.emitters[2].emitDistribution[2] = 0; // end

    // row 4 (fast right car)
    levelEmitters.emitters[3].isActive = true;
    levelEmitters.emitters[3].distIdx = 0;
    levelEmitters.emitters[3].frameCounter = 100;
    levelEmitters.emitters[3].objTemplate.animation = rss.fastRightCarAnim;
    levelEmitters.emitters[3].objTemplate.animation.position = {0.0f, CARS_4_Y};
    levelEmitters.emitters[3].objTemplate.isActive = true;
    levelEmitters.emitters[3].objTemplate.velocity = {0.9f, 0.0f};
    levelEmitters.emitters[3].emitDistribution[0] = 210;
    levelEmitters.emitters[3].emitDistribution[1] = 0;

    // row 5 (truck)
    levelEmitters.emitters[4].isActive = true;
    levelEmitters.emitters[4].distIdx = 0;
    levelEmitters.emitters[4].frameCounter = 165;
    levelEmitters.emitters[4].objTemplate.animation = rss.truckAnim;
    levelEmitters.emitters[4].objTemplate.animation.position = {rss.screen.width, CARS_5_Y};
    levelEmitters.emitters[4].objTemplate.isActive = true;
    levelEmitters.emitters[4].objTemplate.velocity = {-0.5f, 0.0f};
    levelEmitters.emitters[4].emitDistribution[0] = 300;
    levelEmitters.emitters[4].emitDistribution[1] = 180;
    levelEmitters.emitters[4].emitDistribution[2] = 0;

    return levelEmitters;
}

LevelsModule levels;
}

