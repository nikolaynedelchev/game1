#pragma once
#include "libs.h"
#include "transform.h"
#include "engine_bridge.h"

namespace dd
{
struct sprite
{
    bool enabled = false;
    bool isLoaded = false;
    point position = {0.0f, 0.0f};
    transform target = {0.0f, 0.0f, 1.0f, 1.0f};
    rectangle source  = {0.0f, 0.0f, 0.0f, 0.0f};
    float rotate = 0.0f;
    uint32_t textureId = 0;
};

namespace gfx
{
    void draw(const ::dd::sprite&);
    //
    ::dd::sprite load_sprite(const string& imageFile, 
                             rectangle sourceRectangle,
                             transform targetTransform);
    //
    void release_spritres();

    point global_pos(const sprite&);
}
}
