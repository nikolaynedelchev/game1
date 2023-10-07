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
    bool collision(const dd::sprite& s1, const dd::bound& b1,
                const dd::sprite& s2, const dd::bound& b2);

    void draw(const dd::sprite& s, const dd::bound& b);
}
}