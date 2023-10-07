#pragma once
#include "engine_bridge.h"
#include <raylib.h>

namespace dd
{

#define CAST_TYPES_LIST(do_macro)                                        \
    do_macro(   Vector2                 ,   ::dd::point                 )\
    do_macro(   Rectangle               ,   ::dd::rectangle             )\
    do_macro(   Color                   ,   ::dd::color                 )\
    do_macro(   Image                   ,   ::dd::image                 )\
    do_macro(   Texture2D               ,   ::dd::texture               )\
    do_macro(   AudioStream             ,   ::dd::audio_stream          )\
    do_macro(   Sound                   ,   ::dd::sound                 )\
    do_macro(   Music                   ,   ::dd::music                 )\
    do_macro(   KeyboardKey             ,   ::dd::keys::kbd_key         )\


//
#define DD_TYPE_CAST(ray_, dd_) \
static inline ray_ cast(const dd_ & val) { return reinterpret_cast< const ray_ & >(val); } \
static inline dd_  cast(const ray_ & val) { return reinterpret_cast< const dd_ & >(val); } \

CAST_TYPES_LIST( DD_TYPE_CAST )

}