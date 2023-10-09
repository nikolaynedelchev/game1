#pragma once
#include "libs.h"
#include "operators.h"
#include "engine_bridge.h"

namespace dd
{
struct transform
{
    vec offset = {0.0f, 0.0f};
    vec scale = {1.0f, 1.0f};
    constexpr transform() = default;
    constexpr transform(dd::vec offset, dd::vec scale) : offset(offset), scale(scale) {}
    constexpr transform(float offset_x, float offset_y, float scale_x, float scale_y) : offset({offset_x, offset_y}), scale({scale_x, scale_y}) {}
};
}

dd::transform operator*(const dd::transform&, const dd::transform&);
dd::transform& operator*=(dd::transform&, const dd::transform&);
//
dd::vec operator*(const dd::vec&, const dd::transform&);
dd::vec operator*(const dd::transform&, const dd::vec&);
dd::vec& operator*=(dd::vec&, const dd::transform&);
//
dd::rect operator*(const dd::rect&, const dd::transform&);
dd::rect operator*(const dd::transform&, const dd::rect&);
dd::rect& operator*=(dd::rect&, const dd::transform&);
//
