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

///////////////////////
// Transforms
dd::transform operator*(const dd::transform& t1, const dd::transform& t2)
{
    auto t = t1;
    t.offset += t2.offset;
    t.scale *= t2.scale;
    return t;
}

dd::transform& operator*=(dd::transform& t1, const dd::transform& t2)
{
    t1.offset += t2.offset;
    t1.scale *= t2.scale;
    return t1;
}

dd::vec operator*(const dd::vec& v1, const dd::transform& t2)
{
    auto v = v1;
    v += t2.offset;
    v *= t2.scale;
    return v;
}

dd::vec operator*(const dd::transform& t1, const dd::vec& v2)
{
    auto v = v2;
    v += t1.offset;
    v *= t1.scale;
    return v;
}

dd::vec& operator*=(dd::vec& v1, const dd::transform& t2)
{
    v1 += t2.offset;
    v1 *= t2.scale;
    return v1;
}

dd::rect operator*(const dd::rect& r1, const dd::transform& t2)
{
    auto r = r1;
    r.x += t2.offset.x;
    r.y += t2.offset.y;
    r.x *= t2.scale.x;
    r.y *= t2.scale.y;
    r.width *= t2.scale.x;
    r.height *= t2.scale.y;
    return r;
}

dd::rect operator*(const dd::transform& t1, const dd::rect& r2)
{
    auto r = r2;
    r.x += t1.offset.x;
    r.y += t1.offset.y;
    r.x *= t1.scale.x;
    r.y *= t1.scale.y;
    r.width *= t1.scale.x;
    r.height *= t1.scale.y;
    return r;
}

dd::rect& operator*=(dd::rect& r1, const dd::transform& t2)
{
    r1.x += t2.offset.x;
    r1.y += t2.offset.y;
    r1.x *= t2.scale.x;
    r1.y *= t2.scale.y;
    r1.width *= t2.scale.x;
    r1.height *= t2.scale.y;
    return r1;
}
