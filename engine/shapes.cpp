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
    }
}