#include "operators.h"

using namespace dd;

///////////////////////
// Points
dd::point& operator+=(dd::point& v1, const dd::point& v2)
{
    v1.x += v2.x;
    v1.y += v2.y;
    return v1;
}

dd::point operator+(const dd::point& v1, const dd::point& v2)
{
    auto r = v1;
    r.x += v2.x;
    r.y += v2.y;
    return r;
}

dd::point& operator-=(dd::point& v1, const dd::point& v2)
{
    v1.x -= v2.x;
    v1.y -= v2.y;
    return v1;
}

dd::point operator-(const dd::point& v1, const dd::point& v2)
{
    auto r = v1;
    r.x -= v2.x;
    r.y -= v2.y;
    return r;
}

dd::point& operator*=(dd::point& v1, const dd::point& v2)
{
    v1.x *= v2.x;
    v1.y *= v2.y;
    return v1;
}

dd::point operator*(const dd::point& v1, const dd::point& v2)
{
    auto r = v1;
    r.x *= v2.x;
    r.y *= v2.y;
    return r;
}

dd::point& operator/=(dd::point& v1, const dd::point& v2)
{
    v1.x /= v2.x;
    v1.y /= v2.y;
    return v1;
}

dd::point operator/(const dd::point& v1, const dd::point& v2)
{
    auto r = v1;
    r.x /= v2.x;
    r.y /= v2.y;
    return r;
}

dd::point& operator+=(dd::point& v1, float v2)
{
    v1.x += v2;
    v1.y += v2;
    return v1;
}

dd::point operator+(const dd::point& v1, float v2)
{
    auto r = v1;
    r.x += v2;
    r.y += v2;
    return r;
}

dd::point& operator-=(dd::point& v1, float v2)
{
    v1.x -= v2;
    v1.y -= v2;
    return v1;
}

dd::point operator-(const dd::point& v1, float v2)
{
    auto r = v1;
    r.x -= v2;
    r.y -= v2;
    return r;
}

dd::point& operator*=(dd::point& v1, float v2)
{
    v1.x *= v2;
    v1.y *= v2;
    return v1;
}

dd::point operator*(const dd::point& v1, float v2)
{
    auto r = v1;
    r.x *= v2;
    r.y *= v2;
    return r;
}

dd::point& operator/=(dd::point& v1, float v2)
{
    v1.x /= v2;
    v1.y /= v2;
    return v1;
}

dd::point operator/(const dd::point& v1, float v2)
{
    auto r = v1;
    r.x /= v2;
    r.y /= v2;
    return r;
}

dd::point& operator+=(float v1, dd::point& v2)
{
    v2.x += v1;
    v2.y += v1;
    return v2;
}

dd::point operator+(float v1, dd::point& v2)
{
    auto r = v2;
    r.x += v1;
    r.y += v1;
    return r;
}

dd::point& operator-=(float v1, dd::point& v2)
{
    v2.x -= v1;
    v2.y -= v1;
    return v2;
}

dd::point operator-(float v1, dd::point& v2)
{
    auto r = v2;
    r.x -= v1;
    r.y -= v1;
    return r;
}

dd::point& operator*=(float v1, dd::point& v2)
{
    v2.x *= v1;
    v2.y *= v1;
    return v2;
}

dd::point operator*(float v1, dd::point& v2)
{
    auto r = v2;
    r.x *= v1;
    r.y *= v1;
    return r;
}

dd::point& operator/=(float v1, dd::point& v2)
{
    v2.x /= v1;
    v2.y /= v1;
    return v2;
}

dd::point operator/(float v1, dd::point& v2)
{
    auto r = v2;
    r.x /= v1;
    r.y /= v1;
    return r;
}

bool operator==(const dd::point& v1, const dd::point v2)
{
    return v1.x == v2.x && v1.y == v2.y;
}

///////////////////////
// Rects
dd::rect& operator+=(dd::rect& r1, const dd::point& v2)
{
    r1.x += v2.x;
    r1.y += v2.y;
    return r1;
}

dd::rect operator+(const dd::rect& r1, const dd::point& v2)
{
    auto r = r1;
    r.x += v2.x;
    r.y += v2.y;
    return r;
}

dd::rect& operator-=(dd::rect& r1, const dd::point& v2)
{
    r1.x -= v2.x;
    r1.y -= v2.y;
    return r1;
}

dd::rect operator-(const dd::rect& r1, const dd::point& v2)
{
    auto r = r1;
    r.x -= v2.x;
    r.y -= v2.y;
    return r;
}

///////////////////////
// Circles
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
