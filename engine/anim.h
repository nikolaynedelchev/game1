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


    void fps(float);
    float fps() const;
    void add_frame(sprite);
    void play();
    void pause(bool paused = true);
    void restart();
    bool paused() const;
    bool finished() const;
    float duration() const;
    float progress() const;
    float elapsed() const;
    int frame() const;

    void update();
    void draw() const;

    bool collision(const dd::anim& a2) const;
    bool collision(const dd::sprite& s2) const;

    struct
    {
        float fps = 8.0f;
        bool paused = true;
        float elapsed = -1.0f;
        std::vector<sprite> frames;
    }p_;
};

}