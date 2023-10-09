#include "bound.h"
#include "casts.h"
#include "operators.h"

namespace dd
{
namespace gfx
{
    bool collision(const bound &b1, const vec &v1, const bound &b2, const vec &v2)
    {
        for(const auto& r1 : b1.rects)
        {
            for(const auto& r2 : b2.rects)
            {
                if (CheckCollisionRecs(cast(r1 + v1), cast(r2 + v2)))
                {
                    return true;
                }
            }
            for(const auto& c2 : b2.circles)
            {
                if (CheckCollisionCircleRec(cast(c2.center + v2), c2.radius, cast(r1 + v1)))
                {
                    return true;
                }
            }
        }
        for(const auto& c1 : b1.circles)
        {
            for(const auto& r2 : b2.rects)
            {
                if (CheckCollisionCircleRec(cast(c1.center + v1), c1.radius, cast(r2 + v2)))
                {
                    return true;
                }
            }
            for(const auto& c2 : b2.circles)
            {
                if (CheckCollisionCircles(cast(c1.center + v1), c1.radius,
                                        cast(c2.center + v2), c2.radius))
                {
                    return true;
                }
            }
        }
        return false;
    }

    void draw(const bound &b, const vec &v)
    {
        for(const auto& r : b.rects)
        {
            DrawRectangleLines(int(r.x + v.x),
                            int(r.y + v.y),
                            int(r.width),
                            int(r.height), WHITE);
        }
        for(auto circ : b.circles)
        {
            dd::gfx::draw(circ + v, colors::white);
        }
    }
}
}
