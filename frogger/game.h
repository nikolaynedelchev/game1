#pragma once

#include <dd.h>

namespace FroggerGame
{

#define ROWS (12)
#define ROW_H (36)
#define HOMES_H (53)
#define HEADER_H (53)
#define FOOTER_H (44)

#define HOMES_Y (HEADER_H)
#define UPPER_ROW_Y (HOMES_Y + HOMES_H)
#define MID_LAND_Y (UPPER_ROW_Y + 5 * ROW_H)
#define LOWER_ROW_Y (MID_LAND_Y + 5 * ROW_H)
#define LOW_LAND_Y (LOWER_ROW_Y + ROW_H)
#define FOOTER_Y (LOW_LAND_Y + ROW_H)

struct GameModule
{
    float screenWidth = 1440;
    float screenHeight = 900;

    // 700x900
    float width = 400;
    float height = (ROWS * ROW_H + HOMES_H + HEADER_H + FOOTER_H); // 582

    dd::camera camera;
    dd::rect clippingRect;

    int score = 0;
    int lives = 0;
    float remainingTime = 40.0f;
    float levelTime = 40.0f;

    void Init();
    void MainLoop();
    void Deinit();

    void Update();
    void Draw();

    void UpdateCamera();
    void DrawBackground();
    void DrawTime();
    void DrawLives();
    void DrawScore();
};

extern dd::engine engine;
extern GameModule game;


}
