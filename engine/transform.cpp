#include "transform.h"

using namespace dd;


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

dd::rectangle operator*(const dd::rectangle& r1, const dd::transform& t2)
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

dd::rectangle operator*(const dd::transform& t1, const dd::rectangle& r2)
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

dd::rectangle& operator*=(dd::rectangle& r1, const dd::transform& t2)
{
    r1.x += t2.offset.x;
    r1.y += t2.offset.y;
    r1.x *= t2.scale.x;
    r1.y *= t2.scale.y;
    r1.width *= t2.scale.x;
    r1.height *= t2.scale.y;
    return r1;
}
