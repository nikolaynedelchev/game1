#pragma once
#include "engine_bridge.h"

dd::point& operator+=(dd::point& v1, const dd::point& v2);
dd::point operator+(const dd::point& v1, const dd::point& v2);
dd::point& operator-=(dd::point& v1, const dd::point& v2);
dd::point operator-(const dd::point& v1, const dd::point& v2);
dd::point& operator*=(dd::point& v1, const dd::point& v2);
dd::point operator*(const dd::point& v1, const dd::point& v2);
dd::point& operator/=(dd::point& v1, const dd::point& v2);
dd::point operator/(const dd::point& v1, const dd::point& v2);
//
dd::point& operator+=(dd::point& v1, float v2);
dd::point operator+(const dd::point& v1, float v2);
dd::point& operator-=(dd::point& v1, float v2);
dd::point operator-(const dd::point& v1, float v2);
dd::point& operator*=(dd::point& v1, float v2);
dd::point operator*(const dd::point& v1, float v2);
dd::point& operator/=(dd::point& v1, float v2);
dd::point operator/(const dd::point& v1, float v2);
//
dd::point& operator+=(float v1, dd::point& v2);
dd::point operator+(float v1, dd::point& v2);
dd::point& operator-=(float v1, dd::point& v2);
dd::point operator-(float v1, dd::point& v2);
dd::point& operator*=(float v1, dd::point& v2);
dd::point operator*(float v1, dd::point& v2);
dd::point& operator/=(float v1, dd::point& v2);
dd::point operator/(float v1, dd::point& v2);
//
dd::rect& operator+=(dd::rect& r1, const dd::point& v2);
dd::rect operator+(const dd::rect& r1, const dd::point& v2);
dd::rect& operator-=(dd::rect& r1, const dd::point& v2);
dd::rect operator-(const dd::rect& r1, const dd::point& v2);

