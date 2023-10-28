#include "all_modules.h"

namespace FroggerGame
{

void LevelsModule::Init()
{

}

static ObjectEmitter EmptyEmitter()
{
    ObjectEmitter e;
    e.isActive = true;
    e.distIdx = 0;
    e.objTemplate.isActive = true;
    e.objTemplate.velocity = {1.0f, 0.0f};
    for(size_t i = 0; i < 8; i++) e.emitDistribution[i] = 0;
    return e;
}

static ObjectEmitter CreateRow1Car()
{
    ObjectEmitter e = EmptyEmitter();
    e.frameCounter = 35;
    e.objTemplate.animation = rss.fastLeftCarAnim;
    float startingPoint = OFFSCR_MAX;
    e.objTemplate.animation.position = {startingPoint, CARS_1_Y};
    e.objTemplate.velocity *= -0.7f;
    return e;
}

static ObjectEmitter CreateRow2Tractor()
{
    ObjectEmitter e = EmptyEmitter();
    e.frameCounter = 90;
    e.objTemplate.animation = rss.tractorAnim;
    float startingPoint = OFFSCR_MIN;
    e.objTemplate.animation.position = {startingPoint, CARS_2_Y};
    e.objTemplate.velocity *= 0.4f;
    return e;
}

static ObjectEmitter CreateRow3Car()
{
    ObjectEmitter e = EmptyEmitter();
    e.frameCounter = 70;
    e.objTemplate.animation = rss.slowCarAnim;
    float startingPoint = OFFSCR_MAX;
    e.objTemplate.animation.position = {startingPoint, CARS_3_Y};
    e.objTemplate.velocity *= -0.6f;
    return e;
}

static ObjectEmitter CreateRow4Car()
{
    ObjectEmitter e = EmptyEmitter();
    e.frameCounter = 130;
    e.objTemplate.animation = rss.fastRightCarAnim;
    float startingPoint = OFFSCR_MIN;
    e.objTemplate.animation.position = {startingPoint, CARS_4_Y};
    e.objTemplate.velocity *= 1.0f;
    return e;
}

static ObjectEmitter CreateRow5Truck()
{
    ObjectEmitter e = EmptyEmitter();
    e.frameCounter = 130;
    e.objTemplate.animation = rss.truckAnim;
    float startingPoint = OFFSCR_MAX;
    e.objTemplate.animation.position = {startingPoint, CARS_5_Y};
    e.objTemplate.velocity *= -0.5f;
    return e;
}

static ObjectEmitter Create3Turtles()
{
    ObjectEmitter e = EmptyEmitter();
    e.frameCounter = 50;
    e.objTemplate.animation = rss.turtleAnim;
    float startingPoint = OFFSCR_MAX;
    e.objTemplate.animation.position = {startingPoint, WATER_1_Y};
    e.objTemplate.velocity *= -0.3f;
    return e;
}

static ObjectEmitter CreateSmallTree()
{
    ObjectEmitter e = EmptyEmitter();
    e.frameCounter = 50;
    e.objTemplate.animation = rss.smallTreeAnim;
    float startingPoint = OFFSCR_MIN;
    e.objTemplate.animation.position = {startingPoint, WATER_2_Y};
    e.objTemplate.velocity *= 0.5f;
    return e;
}

static ObjectEmitter CreateBigTree()
{
    ObjectEmitter e = EmptyEmitter();
    e.frameCounter = 50;
    e.objTemplate.animation = rss.bigTreeAnim;
    float startingPoint = OFFSCR_MIN;
    e.objTemplate.animation.position = {startingPoint, WATER_3_Y};
    e.objTemplate.velocity *= 0.8f;
    return e;
}

static ObjectEmitter Create2Turtles()
{
    ObjectEmitter e = EmptyEmitter();
    e.frameCounter = 50;
    e.objTemplate.animation = rss.divingTurtleAnim;
    float startingPoint = OFFSCR_MAX;
    e.objTemplate.animation.position = {startingPoint, WATER_4_Y};
    e.objTemplate.velocity *= -0.5f;
    return e;
}


static ObjectEmitter CreateMidTree()
{
    ObjectEmitter e = EmptyEmitter();
    e.frameCounter = 20;
    e.objTemplate.animation = rss.midTreeAnim;
    float startingPoint = OFFSCR_MIN;
    e.objTemplate.animation.position = {startingPoint, WATER_5_Y};
    e.objTemplate.velocity *= 0.8f;
    return e;
}

static ObjectEmitter CreateCrocodile()
{
    ObjectEmitter e = EmptyEmitter();
    e.frameCounter = 20;
    e.objTemplate.animation = rss.crocodileAnim;
    float startingPoint = OFFSCR_MIN;
    e.objTemplate.animation.position = {startingPoint, WATER_5_Y};
    e.objTemplate.velocity *= 0.8f;
    return e;
}

LevelEmitters GetTestLevelObjectEmitter()
{
    LevelEmitters levelEmitters;
    for(auto& e : levelEmitters.emitters) e.isActive = false;

    // row 1 (fast left car)
    levelEmitters.emitters[0] = CreateSmallTree();
    levelEmitters.emitters[0].objTemplate.velocity *= 0.5f;
    levelEmitters.emitters[0].emitDistribution[0] = 400;

    return levelEmitters;
}

LevelEmitters LevelsModule::GetLevelObjectEmitter(int level) const
{
    (void)level;
    //return GetTestLevelObjectEmitter();
    LevelEmitters levelEmitters;
    for(auto& e : levelEmitters.emitters) e.isActive = false;

    float levelSpeed = 0.7f;

    // row 1 (fast left car)
    levelEmitters.emitters[0] = CreateRow1Car();
    levelEmitters.emitters[0].objTemplate.velocity *= levelSpeed;
    levelEmitters.emitters[0].emitDistribution[0] = 290;
    levelEmitters.emitters[0].emitDistribution[1] = 100;
    levelEmitters.emitters[0].emitDistribution[2] = 190;
    levelEmitters.emitters[0].emitDistribution[3] = 100;

    // row 2 (tractor)
    levelEmitters.emitters[1] = CreateRow2Tractor();
    levelEmitters.emitters[1].objTemplate.velocity *= levelSpeed;
    levelEmitters.emitters[1].emitDistribution[0] = 380;

    // row 3 (slow left car)
    levelEmitters.emitters[2] = CreateRow3Car();
    levelEmitters.emitters[2].objTemplate.velocity *= levelSpeed;
    levelEmitters.emitters[2].emitDistribution[0] = 350;
    levelEmitters.emitters[2].emitDistribution[1] = 120;

    // row 4 (fast right car)
    levelEmitters.emitters[3] = CreateRow4Car();
    levelEmitters.emitters[3].objTemplate.velocity *= levelSpeed;
    levelEmitters.emitters[3].emitDistribution[0] = 210;

    // row 5 (truck)
    levelEmitters.emitters[4] = CreateRow5Truck();
    levelEmitters.emitters[4].objTemplate.velocity *= levelSpeed;
    levelEmitters.emitters[4].emitDistribution[0] = 360;
    levelEmitters.emitters[4].emitDistribution[1] = 250;

    // water 1 (3 x turtles)
    levelEmitters.emitters[5] = Create3Turtles();
    levelEmitters.emitters[5].objTemplate.velocity *= levelSpeed;
    levelEmitters.emitters[5].emitDistribution[0] = 300;
    levelEmitters.emitters[5].emitDistribution[1] = 180;

    // water 2 (small tree)
    levelEmitters.emitters[6] = CreateSmallTree();
    levelEmitters.emitters[6].objTemplate.velocity *= levelSpeed;
    levelEmitters.emitters[6].emitDistribution[0] = 400;

    // water 3 (big tree)
    levelEmitters.emitters[7] = CreateBigTree();
    levelEmitters.emitters[7].objTemplate.velocity *= levelSpeed;
    levelEmitters.emitters[7].emitDistribution[0] = 500;

    // water 4 (2 x turtles)
    levelEmitters.emitters[8] = Create2Turtles();
    levelEmitters.emitters[8].objTemplate.velocity *= levelSpeed;
    levelEmitters.emitters[8].emitDistribution[0] = 200;
    levelEmitters.emitters[8].emitDistribution[1] = 120;

    // water 5 (mid tree)
    levelEmitters.emitters[9] = CreateMidTree();
    levelEmitters.emitters[9].objTemplate.velocity *= levelSpeed;
    levelEmitters.emitters[9].emitDistribution[0] = 700;
    levelEmitters.emitters[9].frameCounter = 250;

    // water 5 (crocodile)
    levelEmitters.emitters[10] = CreateCrocodile();
    levelEmitters.emitters[10].objTemplate.velocity *= levelSpeed;
    levelEmitters.emitters[10].emitDistribution[0] = 700;
    levelEmitters.emitters[10].frameCounter = 0;
    levelEmitters.emitters[10].name = "crocodile";

    return levelEmitters;
}

LevelsModule levels;
}

