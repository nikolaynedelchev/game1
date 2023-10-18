﻿#pragma once
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

struct bound
{
    std::vector<rect> rects;
    std::vector<circle> circles;

    void draw(const vec& v) const;
    static bool collision(const bound& b1, const vec& v1,
                          const bound& b2, const vec& v2);
};

struct sprite
{
    bool visible = false;
    dd::point position;
    dd::vec anchor;
    dd::vec size;
    dd::rect source;
    float rotate = 0.0f;

    bool flip_x = false;
    bool flip_y = false;
    dd::bound bound;

    uint32_t texture_id = 0;
    bool loaded = false;



    void draw() const;
    //
    void load(const std::string& imageFile, 
              dd::rect sourceRectangle,
              dd::vec size);
    //
    void change_anchor(dd::anchors);
    dd::rect rect() const;
    static void release_spritres();
    bool collision(const sprite& s2) const;
};


struct anim
{
    bool visible = false;
    dd::point position;
    dd::vec anchor;
    dd::vec size;
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
    void change_anchor(dd::anchors);

    bool collision(const anim& a2) const;
    bool collision(const sprite& s2) const;

private: struct
    {
        float fps = 8.0f;
        bool paused = true;
        float elapsed = -1.0f;
        std::vector<sprite> frames;
    }p_;
};

struct sound
{
    void load(const std::string& file);
    void play();

    private: struct
    {
        sound_impl sound_;
    }p_;  
};

struct text
{
    std::string symbols;
    point position;
    float font_size = 0;
    dd::color color = colors::white;
    text() = default;
    text(std::string txt, dd::point pos, float sz, dd::color c) : symbols(std::move(txt)), position(pos), font_size(sz), color(c){}
    void draw() const;
    void clear_background(dd::color color) const;
    dd::vec size() const;
    // text
    void set_font(const std::string& font);
    void set_font_default();

    private: struct
    {
        font text_font;
        bool has_default_font = false;
    }p_;
};

}
