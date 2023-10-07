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
};
}

dd::transform operator*(const dd::transform&, const dd::transform&);
dd::transform& operator*=(dd::transform&, const dd::transform&);
//
dd::vec operator*(const dd::vec&, const dd::transform&);
dd::vec operator*(const dd::transform&, const dd::vec&);
dd::vec& operator*=(dd::vec&, const dd::transform&);
//
dd::rectangle operator*(const dd::rectangle&, const dd::transform&);
dd::rectangle operator*(const dd::transform&, const dd::rectangle&);
dd::rectangle& operator*=(dd::rectangle&, const dd::transform&);
//
