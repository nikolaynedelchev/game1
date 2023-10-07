#pragma once
#include "libs.h"
#include "engine_bridge.h"

namespace dd
{
struct circle
{
    point center;
    float radius;
};
}

dd::circle& operator+=(dd::circle& c1, const dd::point& v2);
dd::circle operator+(const dd::circle& c1, const dd::point& v2);
dd::circle& operator-=(dd::circle& c1, const dd::point& v2);
dd::circle operator-(const dd::circle& c1, const dd::point& v2);
dd::circle& operator*=(dd::circle& c1, const float& v2);
dd::circle operator*(const dd::circle& c1, const float& v2);
dd::circle& operator/=(dd::circle& c1, const float& v2);
dd::circle operator/(const dd::circle& c1, const float& v2);

namespace dd
{
    namespace gfx
    {
        void draw(const dd::circle&, color, bool filled = false);
        void draw(const dd::rectangle&, color, bool filled = false);
        void draw(const dd::point&, color, bool bold = false);
    }
}