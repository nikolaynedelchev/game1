#pragma once
#include "libs.h"
#include "sprite.h"
#include "shapes.h"

namespace dd
{
struct bound
{
    vector<rect> rects;
    vector<circle> circles;
};

namespace gfx
{
    bool collision(const dd::bound& b1, const dd::sprite& s1,
                   const dd::bound& b2, const dd::sprite& s2);

    void draw(const dd::bound& b, const dd::sprite& s);
}
}