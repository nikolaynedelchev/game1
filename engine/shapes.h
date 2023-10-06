#pragma once
#include "libs.h"

struct Circle
{
    Vector2 center;
    float radius;
};

Circle& operator+=(Circle& c1, const Vector2& v2);
Circle operator+(const Circle& c1, const Vector2& v2);
Circle& operator-=(Circle& c1, const Vector2& v2);
Circle operator-(const Circle& c1, const Vector2& v2);
Circle& operator*=(Circle& c1, const float& v2);
Circle operator*(const Circle& c1, const float& v2);
Circle& operator/=(Circle& c1, const float& v2);
Circle operator/(const Circle& c1, const float& v2);

void DrawCircle(const Circle&, Color, bool filled = false);