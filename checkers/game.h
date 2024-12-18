﻿#pragma once
#include <dd.h>

namespace ndn::CheckersGame
{

struct GameModule
{
    float systemWidth = 1440;
    float systemHeight = 900;

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
};

extern dd::engine engine;
extern GameModule game;


}

