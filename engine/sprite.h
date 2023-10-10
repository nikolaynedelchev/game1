#pragma once
#include "libs.h"
#include "engine_bridge.h"

namespace dd
{
struct sprite
{
    bool visible = false;
    point position = {0.0f, 0.0f};
    transform target = {0.0f, 0.0f, 1.0f, 1.0f};
    rect source  = {0.0f, 0.0f, 0.0f, 0.0f};
    float rotate = 0.0f;
    uint32_t texture_id = 0;
    bool flip_x = false;
    bool flip_y = false;
    bool loaded = false;
    dd::bound bound;
};

namespace gfx
{
    void draw(const ::dd::sprite&);
    //
    ::dd::sprite load_sprite(const string& imageFile, 
                             rect sourceRectangle,
                             transform targetTransform);
    //
    void release_spritres();

    point global_pos(const sprite&);
    rect global_rect(const sprite&);
    rect origin_rect(const sprite&);

    bool collision(const dd::sprite& s1, const dd::sprite& s2);

}
}
