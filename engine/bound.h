#pragma once
#include "libs.h"
#include "sprite.h"
#include "shapes.h"

struct Bound
{
    vector<Rectangle> rects;
    vector<Circle> circles;
};

bool CheckCollision(const Sprite& s1, const Bound& b1,
                    const Sprite& s2, const Bound& b2);

void DrawBound(const Sprite& s, const Bound& b);
