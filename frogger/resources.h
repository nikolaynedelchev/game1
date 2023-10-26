#pragma once

#include <dd.h>

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
#define ROWS (12)
#define ROW_H (36.0f)
#define HOMES_H (53.0f)
#define HEADER_H (53.0f)
#define FOOTER_H (44.0f)

#define HOMES_Y (HEADER_H)
#define UPPER_ROW_Y (HOMES_Y + HOMES_H)
#define MID_LAND_Y (UPPER_ROW_Y + 5.0f * ROW_H)
#define LOWER_ROW_Y (MID_LAND_Y + 5.0f * ROW_H)
#define LOW_LAND_Y (LOWER_ROW_Y + ROW_H)
#define FOOTER_Y (LOW_LAND_Y + ROW_H)

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

    dd::sprite turtle[3];
    dd::sprite turtleDive[2];

    dd::sprite trees[3];

    dd::sprite walkway;
    dd::sprite homesBackground;

    dd::sprite froggerLogo;

    dd::rect screen = {0.0f, 0.0f, SCREEN_WIDTH, (ROWS * ROW_H + HOMES_H + HEADER_H + FOOTER_H)}; // {0,0,400,582}

    dd::rect homes[5];
    dd::rect homeWalls[6];
    dd::rect riverRect;
    dd::rect landRect;

    dd::sprite skull_1;
    dd::sprite skull_2;

    dd::sound music;
    dd::sound extraLife;
    dd::sound hit;
    dd::sound jump;
    dd::sound time;
    dd::sound drown;

    dd::vec hJumpSize = {27.0f, 0.0f};
    dd::vec vJumpSize = {0.0f, 36.0f};
    float jumpFrames = 6;
    dd::vec jumpingMinPos = {10.0f, HOMES_Y + HOMES_H / 2.0f};
    dd::vec jumpingMaxPos = {SCREEN_WIDTH - 10.0f, LOW_LAND_Y + ROW_H / 2.0f};
};

extern ResourcesModule rss;
}
