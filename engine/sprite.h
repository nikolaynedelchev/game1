#pragma once
#include "engine.h"

struct Sprite
{
    bool enabled = false;
    bool isLoaded = false;
    Rectangle position = {0.0f, 0.0f, 0.0f, 0.0f};
    Rectangle sourceSubimage = {0.0f, 0.0f, 0.0f, 0.0f};
    float rotate = 0.0f;
    uint32_t textureId = 0;
};

Sprite CreateSprite(const string& imageFile, Rectangle sourceSubimage);
void ReleaseSpritres();
void DrawSprite(const Sprite&);
