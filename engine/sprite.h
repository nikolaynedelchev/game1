#pragma once
#include "libs.h"

struct Sprite
{
    bool enabled = false;
    bool isLoaded = false;
    Vector2 position = {0.0f, 0.0f};
    Rectangle targetShape = {0.0f, 0.0f, 0.0f, 0.0f};
    Rectangle sourceShape = {0.0f, 0.0f, 0.0f, 0.0f};
    float rotate = 0.0f;
    uint32_t textureId = 0;
};

Sprite CreateSprite(const string& imageFile, 
                    Rectangle sourceShape, 
                    float scale = 1.0f, 
                    Vector2 offset = {0.0f, 0.0f});
void ReleaseSpritres();
void DrawSprite(const Sprite&);
