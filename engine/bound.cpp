#include "bound.h"
#include "casts.h"
#include "operators.h"

namespace dd
{
    namespace gfx
    {
        bool collision(const sprite &s1, const bound &b1, const sprite &s2, const bound &b2)
        {
            for(const auto& r1 : b1.rects)
            {
                for(const auto& r2 : b2.rects)
                {
                    if (CheckCollisionRecs(cast(r1 + s1.position), cast(r2 + s2.position)))
                    {
                        return true;
                    }
                }
                for(const auto& c2 : b2.circles)
                {
                    if (CheckCollisionCircleRec(cast(c2.center + s2.position), c2.radius, cast(r1 + s1.position)))
                    {
                        return true;
                    }
                }
            }
            for(const auto& c1 : b1.circles)
            {
                for(const auto& r2 : b2.rects)
                {
                    if (CheckCollisionCircleRec(cast(c1.center + s1.position), c1.radius, cast(r2 + s2.position)))
                    {
                        return true;
                    }
                }
                for(const auto& c2 : b2.circles)
                {
                    if (CheckCollisionCircles(cast(c1.center + s1.position), c1.radius,
                                            cast(c2.center + s2.position), c2.radius))
                    {
                        return true;
                    }
                }
            }
            return false;
        }

        void draw(const sprite &s, const bound &b)
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
                dd::gfx::draw(circ + s.position, colors::white);
            }
        }
    }
}
