#pragma once
#include "libs.h"
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
    bool collision(const dd::bound& b1, const dd::vec& v1,
                   const dd::bound& b2, const dd::vec& v2);

    void draw(const dd::bound& b, const dd::vec& v);
}
}