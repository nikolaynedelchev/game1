#pragma once
#include "engine_bridge.h"
#include "engine_ex.h"

// Points
dd::point& operator+=(dd::point& v1, const dd::point& v2);
dd::point operator+(const dd::point& v1, const dd::point& v2);
dd::point& operator-=(dd::point& v1, const dd::point& v2);
dd::point operator-(const dd::point& v1, const dd::point& v2);
dd::point& operator*=(dd::point& v1, const dd::point& v2);
dd::point operator*(const dd::point& v1, const dd::point& v2);
dd::point& operator/=(dd::point& v1, const dd::point& v2);
dd::point operator/(const dd::point& v1, const dd::point& v2);
dd::point& operator+=(dd::point& v1, float v2);
dd::point operator+(const dd::point& v1, float v2);
dd::point& operator-=(dd::point& v1, float v2);
dd::point operator-(const dd::point& v1, float v2);
dd::point& operator*=(dd::point& v1, float v2);
dd::point operator*(const dd::point& v1, float v2);
dd::point& operator/=(dd::point& v1, float v2);
dd::point operator/(const dd::point& v1, float v2);
bool operator==(const dd::point& v1, const dd::point v2);
//
dd::point& operator+=(float v1, dd::point& v2);
dd::point operator+(float v1, dd::point& v2);
dd::point& operator-=(float v1, dd::point& v2);
dd::point operator-(float v1, dd::point& v2);
dd::point& operator*=(float v1, dd::point& v2);
dd::point operator*(float v1, dd::point& v2);
dd::point& operator/=(float v1, dd::point& v2);
dd::point operator/(float v1, dd::point& v2);

// Rects
dd::rect& operator+=(dd::rect& r1, const dd::point& v2);
dd::rect operator+(const dd::rect& r1, const dd::point& v2);
dd::rect& operator-=(dd::rect& r1, const dd::point& v2);
dd::rect operator-(const dd::rect& r1, const dd::point& v2);

// Circles
dd::circle& operator+=(dd::circle& c1, const dd::point& v2);
dd::circle operator+(const dd::circle& c1, const dd::point& v2);
dd::circle& operator-=(dd::circle& c1, const dd::point& v2);
dd::circle operator-(const dd::circle& c1, const dd::point& v2);
dd::circle& operator*=(dd::circle& c1, const float& v2);
dd::circle operator*(const dd::circle& c1, const float& v2);
dd::circle& operator/=(dd::circle& c1, const float& v2);
dd::circle operator/(const dd::circle& c1, const float& v2);

// Transforms
dd::transform operator*(const dd::transform&, const dd::transform&);
dd::transform& operator*=(dd::transform&, const dd::transform&);
dd::vec operator*(const dd::vec&, const dd::transform&);
dd::vec operator*(const dd::transform&, const dd::vec&);
dd::vec& operator*=(dd::vec&, const dd::transform&);
dd::rect operator*(const dd::rect&, const dd::transform&);
dd::rect operator*(const dd::transform&, const dd::rect&);
dd::rect& operator*=(dd::rect&, const dd::transform&);