#include "operators.h"


Vector2& operator+=(Vector2& v1, const Vector2& v2)
{
    v1.x += v2.x;
    v1.y += v2.y; 
    return v1;   
}

Rectangle& operator+=(Rectangle& r1, const Vector2& v2)
{
    r1.x += v2.x;
    r1.y += v2.y; 
    return r1;   
}

Vector2 operator+(const Vector2& v1, const Vector2& v2)
{
    Vector2 r;
    r.x = v1.x + v2.x;
    r.y = v1.y + v2.y;
    return r;
}

Rectangle operator+(const Rectangle& r1, const Vector2& v2)
{
    Rectangle r;
    r.x = r1.x + v2.x;
    r.y = r1.y + v2.y;
    r.width = r1.width;
    r.height = r1.height;
    return r;
}

//

Vector2& operator-=(Vector2& v1, const Vector2& v2)
{
    v1.x -= v2.x;
    v1.y -= v2.y; 
    return v1;   
}

Rectangle& operator-=(Rectangle& r1, const Vector2& v2)
{
    r1.x -= v2.x;
    r1.y -= v2.y; 
    return r1;   
}

Vector2 operator-(const Vector2& v1, const Vector2& v2)
{
    Vector2 r;
    r.x = v1.x - v2.x;
    r.y = v1.y - v2.y;
    return r;
}

Rectangle operator-(const Rectangle& r1, const Vector2& v2)
{
    Rectangle r;
    r.x = r1.x - v2.x;
    r.y = r1.y - v2.y;
    r.width = r1.width;
    r.height = r1.height;
    return r;
}

////


Vector2& operator*=(Vector2& v1, const float& v2)
{
    v1.x *= v2;
    v1.y *= v2; 
    return v1;   
}

Rectangle& operator*=(Rectangle& r1, const float& v2)
{
    r1.width *= v2;
    r1.height *= v2; 
    return r1;   
}

Vector2 operator*(const Vector2& v1, const float& v2)
{
    Vector2 r;
    r.x = v1.x * v2;
    r.y = v1.y * v2;
    return r;
}

Rectangle operator*(const Rectangle& r1, const float& v2)
{
    Rectangle r;
    r.width = r1.width + v2;
    r.height = r1.height + v2;
    r.x = r1.x;
    r.y = r1.y;
    return r;
}

//

Vector2& operator/=(Vector2& v1, const float& v2)
{
    v1.x /= v2;
    v1.y /= v2; 
    return v1;   
}

Rectangle& operator/=(Rectangle& r1, const float& v2)
{
    r1.width /= v2;
    r1.height /= v2; 
    return r1;   
}

Vector2 operator/(const Vector2& v1, const float& v2)
{
    Vector2 r;
    r.x = v1.x / v2;
    r.y = v1.y / v2;
    return r;
}

Rectangle operator/(const Rectangle& r1, const float& v2)
{
    Rectangle r;
    r.width = r1.width / v2;
    r.height = r1.height / v2;
    r.x = r1.x;
    r.y = r1.y;
    return r;
}