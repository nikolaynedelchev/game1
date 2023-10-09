#pragma once
#include "libs.h"
#include "transform.h"
#include "engine_bridge.h"
#include "sprite.h"
#include "bound.h"

namespace dd
{
struct anim
{
    bool visible = false;
    point position = {0.0f, 0.0f};
    transform target = {0.0f, 0.0f, 1.0f, 1.0f};
    float rotate = 0.0f;
    bool flip_x = false;
    bool flip_y = false;

    bool loop = false;

    struct
    {
        float fps = 8.0f;
        bool paused = true;
        float elapsed = 0.0f;
        std::vector<sprite> frames;
    } privates;
};
namespace gfx
{
    void fps(anim&, float);
    float fps(const anim&);
    void add_frame(anim&, sprite);
    void play(anim&);
    void pause(anim&, bool paused = true);
    void restart(anim&);
    bool paused(const anim&);
    bool finished(const anim&);
    float duration(const anim&);
    float progress(const anim&);
    float elapsed(const anim&);
    int frame(const anim& a);

    void update(anim&);
    void draw(const anim&);

    bool collision(const dd::anim& a1, const dd::anim& a2);
    bool collision(const dd::anim& a1, const dd::sprite& s2);                   
}

}