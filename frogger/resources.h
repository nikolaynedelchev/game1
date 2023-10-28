#pragma once

#include "all_types.h"

#define SMALL 0
#define MID 1
#define BIG 2
#define FED 0
#define HUNGRY 1
#define GND 0
#define AIR 1
#define LEFT_SLOW 0
#define RIGHT_FAST 1
#define LEFT_FAST 2

#define SCREEN_WIDTH (400.0f)

#define OFFSCR_MIN (-89.0f)
#define OFFSCR_MAX (SCREEN_WIDTH + 89.0f)

#define ROWS (12)
#define ROW_H (36.0f)
#define HOMES_H (53.0f)
#define HEADER_H (53.0f)
#define FOOTER_H (44.0f)

#define HOMES_Y (HEADER_H)
#define UPPER_ROW_Y (HOMES_Y + HOMES_H)
#define MID_LAND_Y (UPPER_ROW_Y + 5.0f * ROW_H)
#define UPPER_LAND_ROW_Y (MID_LAND_Y + ROW_H)
#define LOWER_ROW_Y (MID_LAND_Y + 5.0f * ROW_H)
#define LOW_LAND_Y (LOWER_ROW_Y + ROW_H)
#define FOOTER_Y (LOW_LAND_Y + ROW_H)

#define CARS_1_Y ( LOWER_ROW_Y + ROW_H / 2.0f)
#define CARS_2_Y ( CARS_1_Y - ROW_H )
#define CARS_3_Y ( CARS_2_Y - ROW_H )
#define CARS_4_Y ( CARS_3_Y - ROW_H )
#define CARS_5_Y ( CARS_4_Y - ROW_H )

#define WATER_1_Y ( MID_LAND_Y - ROW_H / 2.0f)
#define WATER_2_Y ( WATER_1_Y - ROW_H )
#define WATER_3_Y ( WATER_2_Y - ROW_H )
#define WATER_4_Y ( WATER_3_Y - ROW_H )
#define WATER_5_Y ( WATER_4_Y - ROW_H )

namespace FroggerGame
{

struct ResourcesModule
{
    void Load();
    dd::sprite froggerUp[2];
    dd::sprite froggerDn[2];
    dd::sprite froggerLf[2];
    dd::sprite froggerRg[2];

    dd::sprite ladyLf[2];
    dd::sprite ladyRg[2];

    dd::sprite snake[4];
    dd::sprite cars[3];
    dd::sprite tractors[3];

    dd::sprite beaver[3];

    dd::sprite fly;
    dd::sprite truck;
    dd::sprite crocodile[2];

    dd::sprite emptySprite;
    dd::sprite turtle[3];
    dd::sprite turtleDive[2];

    dd::sprite trees[3];

    dd::sprite walkway;
    dd::sprite homesBackground;

    dd::sprite froggerLogo;

    dd::sprite skull_1;
    dd::sprite skull_2;

    dd::anim tractorAnim;
    dd::anim fastLeftCarAnim;
    dd::anim fastRightCarAnim;
    dd::anim slowCarAnim;
    dd::anim truckAnim;

    dd::anim landDeathAnim;

    dd::anim smallTreeAnim;
    dd::anim midTreeAnim;
    dd::anim bigTreeAnim;
    dd::anim turtleAnim;
    dd::anim divingTurtleAnim;
    dd::anim crocodileAnim;



    dd::rect screen = {0.0f, 0.0f, SCREEN_WIDTH, (ROWS * ROW_H + HOMES_H + HEADER_H + FOOTER_H)}; // {0,0,400,582}

    dd::rect homes[5];
    dd::rect homeWalls[6];
    dd::rect riverRect;
    dd::rect landRect;



    dd::sound music;
    dd::sound extraLife;
    dd::sound hit;
    dd::sound jump;
    dd::sound time;
    dd::sound drown;

    dd::vec hJumpSize = {27.0f, 0.0f};
    dd::vec vJumpSize = {0.0f, 36.0f};
    float jumpFrames = 9; //6
    dd::vec jumpingMinPos = {10.0f, HOMES_Y + HOMES_H / 2.0f};
    dd::vec jumpingMaxPos = {SCREEN_WIDTH - 10.0f, LOW_LAND_Y + ROW_H / 2.0f};
};

extern ResourcesModule rss;
}


/*

Homes Start: 53
Homes Mid: 79.5
Homes End: 106
Water 5, Start: 106, Mid: 124, End: 142
Water 4, Start: 142, Mid: 160, End: 178
Water 3, Start: 178, Mid: 196, End: 214
Water 2, Start: 214, Mid: 232, End: 250
Water 1, Start: 250, Mid: 268, End: 286
Mid Land Start: 286
Mid Land Mid: 304
Mid Land End: 322
Land 5, Start: 322, Mid: 340, End: 358
Land 4, Start: 358, Mid: 376, End: 394
Land 3, Start: 394, Mid: 412, End: 430
Land 2, Start: 430, Mid: 448, End: 466
Land 1, Start: 466, Mid: 484, End: 502
Low Land Start: 502
Low Land Mid: 520
Low Land End: 538


*/
