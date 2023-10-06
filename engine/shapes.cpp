#include "shapes.h"


Circle& operator+=(Circle& c1, const Vector2& v2)
{
    c1.center += v2;
    return c1;
}
Circle operator+(const Circle& c1, const Vector2& v2)
{
    auto res = c1;
    res.center += v2;
    return res;
}
Circle& operator-=(Circle& c1, const Vector2& v2)
{
    c1.center -= v2;
    return c1;
}
Circle operator-(const Circle& c1, const Vector2& v2)
{
    auto res = c1;
    res.center -= v2;
    return res;
}
Circle& operator*=(Circle& c1, const float& v2)
{
    c1.radius *= v2;
    return c1;
}
Circle operator*(const Circle& c1, const float& v2)
{
    auto res = c1;
    res.radius *= v2;
    return res;
}
Circle& operator/=(Circle& c1, const float& v2)
{
    c1.radius /= v2;
    return c1;
}
Circle operator/(const Circle& c1, const float& v2)
{
    auto res = c1;
    res.radius /= v2;
    return res;
}

void DrawCircle(const Circle& circle, Color color, bool filled)
{
    if (filled)
    {
        DrawCircle(int(circle.center.x),
                   int(circle.center.y),
                   circle.radius, color);
    }
    else
    {
        DrawCircleLines(int(circle.center.x),
                        int(circle.center.y),
                        circle.radius, color);
    }
}