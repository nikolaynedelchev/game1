#pragma once
#include "libs.h"
#include "engine_bridge.h"

namespace dd
{
    
struct circle
{
    point center;
    float radius = 0.0f;

    constexpr circle() = default;
    constexpr circle(point c, float r) : center(c), radius(r){}
    constexpr circle(float x, float y, float r) : center({x, y}), radius(r){}

    void draw(color, bool filled = false) const;
};

struct transform
{
    vec offset = {0.0f, 0.0f};
    vec scale = {1.0f, 1.0f};
    constexpr transform() = default;
    constexpr transform(dd::vec offset, dd::vec scale) : offset(offset), scale(scale) {}
    constexpr transform(float offset_x, float offset_y, float scale_x, float scale_y) : offset({offset_x, offset_y}), scale({scale_x, scale_y}) {}
};

struct bound
{
    std::vector<rect> rects;
    std::vector<circle> circles;

    void draw(const dd::vec& v) const;
    static bool collision(const dd::bound& b1, const dd::vec& v1,
                          const dd::bound& b2, const dd::vec& v2);
};

struct sprite
{
    bool visible = false;
    point position = {0.0f, 0.0f};
    transform target = {0.0f, 0.0f, 1.0f, 1.0f};
    rect source  = {0.0f, 0.0f, 0.0f, 0.0f};
    float rotate = 0.0f;

    bool flip_x = false;
    bool flip_y = false;
    dd::bound bound;

    uint32_t texture_id = 0;
    bool loaded = false;



    void draw() const;
    //
    static ::dd::sprite load(const string& imageFile, 
                            rect sourceRectangle,
                            transform targetTransform);
    //
    static void release_spritres();

    point global_pos() const;
    rect global_rect() const;
    rect origin_rect() const;
    bool collision(const dd::sprite& s2) const;
};


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

private: struct
    {
        float fps = 8.0f;
        bool paused = true;
        float elapsed = -1.0f;
        std::vector<sprite> frames;
    }p_;
};

}