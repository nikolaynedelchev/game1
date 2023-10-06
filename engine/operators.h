#pragma once
#include <raylib.h>

Vector2& operator+=(Vector2& v1, const Vector2& v2);
Rectangle& operator+=(Rectangle& r1, const Vector2& v2);

Vector2 operator+(const Vector2& v1, const Vector2& v2);
Rectangle operator+(const Rectangle& r1, const Vector2& v2);

//

Vector2& operator-=(Vector2& v1, const Vector2& v2);
Rectangle& operator-=(Rectangle& r1, const Vector2& v2);

Vector2 operator-(const Vector2& v1, const Vector2& v2);
Rectangle operator-(const Rectangle& r1, const Vector2& v2);

//

Vector2& operator*=(Vector2& v1, const float& v2);
Rectangle& operator*=(Rectangle& r1, const float& v2);

Vector2 operator*(const Vector2& v1, const float& v2);
Rectangle operator*(const Rectangle& r1, const float& v2);

//

Vector2& operator/=(Vector2& v1, const float& v2);
Rectangle& operator/=(Rectangle& r1, const float& v2);

Vector2 operator/(const Vector2& v1, const float& v2);
Rectangle operator/(const Rectangle& r1, const float& v2);