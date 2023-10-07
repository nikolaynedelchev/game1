#include "shapes.h"
#include "casts.h"

using namespace dd;

circle& operator+=(circle& c1, const point& v2)
{
    c1.center += v2;
    return c1;
}
circle operator+(const circle& c1, const point& v2)
{
    auto res = c1;
    res.center += v2;
    return res;
}
circle& operator-=(circle& c1, const point& v2)
{
    c1.center -= v2;
    return c1;
}
circle operator-(const circle& c1, const point& v2)
{
    auto res = c1;
    res.center -= v2;
    return res;
}
circle& operator*=(circle& c1, const float& v2)
{
    c1.radius *= v2;
    return c1;
}
circle operator*(const circle& c1, const float& v2)
{
    auto res = c1;
    res.radius *= v2;
    return res;
}
circle& operator/=(circle& c1, const float& v2)
{
    c1.radius /= v2;
    return c1;
}
circle operator/(const circle& c1, const float& v2)
{
    auto res = c1;
    res.radius /= v2;
    return res;
}

namespace dd
{
namespace gfx
{
    void draw(const ::dd::circle& circle, color color, bool filled)
    {
        if (filled)
        {
            DrawCircle(int(circle.center.x),
                    int(circle.center.y),
                    circle.radius, cast(color));
        }
        else
        {
            DrawCircleLines(int(circle.center.x),
                            int(circle.center.y),
                            circle.radius, cast(color));
        }
    }

    void draw(const rect& r, color c, bool filled)
    {
        if (filled)
        {
            DrawRectangle(int(r.x), int(r.y), int(r.width), int(r.height), cast(c));
        }
        else
        {
            DrawRectangleLines(int(r.x), int(r.y), int(r.width), int(r.height), cast(c));
        }
    }

    void draw(const point& p, color c, bool bold)
    {
        if (bold)
        {
            draw(circle{p, 3.0f}, c, true);
        }
        else
        {
            DrawPixel(int(p.x), int(p.y), cast(c));
        }
    }
}
}