#include "bound.h"

bool CheckCollision(const Sprite &s1, const Bound &b1, const Sprite &s2, const Bound &b2)
{
    for(const auto& r1 : b1.rects)
    {
        for(const auto& r2 : b2.rects)
        {
            if (CheckCollisionRecs(r1 + s1.position, r2 + s2.position))
            {
                return true;
            }
        }
        for(const auto& c2 : b2.circles)
        {
            if (CheckCollisionCircleRec(c2.center + s2.position, c2.radius, r1 + s1.position))
            {
                return true;
            }
        }
    }
    for(const auto& c1 : b1.circles)
    {
        for(const auto& r2 : b2.rects)
        {
            if (CheckCollisionCircleRec(c1.center + s1.position, c1.radius, r2 + s2.position))
            {
                return true;
            }
        }
        for(const auto& c2 : b2.circles)
        {
            if (CheckCollisionCircles(c1.center + s1.position, c1.radius,
                                      c2.center + s2.position, c2.radius))
            {
                return true;
            }
        }
    }
    return false;
}

void DrawBound(const Sprite &s, const Bound &b)
{
    for(const auto& r : b.rects)
    {
        DrawRectangleLines(int(r.x + s.position.x),
                           int(r.y + s.position.y),
                           int(r.width),
                           int(r.height), WHITE);
    }
    for(auto circ : b.circles)
    {
        DrawCircle(circ + s.position, WHITE);
    }
}
