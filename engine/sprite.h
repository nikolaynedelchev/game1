#pragma once
#include "tools.h"

struct Sprite
{
    bool enabled = false;
    bool isLoaded = false;
    Rectangle position;
    Rectangle sourceSubimage;
    float rotate = 0.0f;
    Texture2D texture;
};

void Sprite_Load(Sprite&, string imageKey);
void Sprite_Load(Sprite&, Rectangle sourceSubimage, string imageKey);

void Sprite_Unload(Sprite&);
void Sprite_Draw(const Sprite&);

void test_loader();
