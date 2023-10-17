#pragma once
#include "engine_bridge.h"
#include <raylib.h>

namespace dd
{

#define DD_CAST_TYPES_LIST(do_macro)                                     \
    do_macro(   Vector2                 ,   ::dd::point                 )\
    do_macro(   Rectangle               ,   ::dd::rect                  )\
    do_macro(   Color                   ,   ::dd::color                 )\
    do_macro(   Image                   ,   ::dd::image                 )\
    do_macro(   Texture2D               ,   ::dd::texture               )\
    do_macro(   AudioStream             ,   ::dd::audio_stream          )\
    do_macro(   Sound                   ,   ::dd::sound_impl            )\
    do_macro(   Music                   ,   ::dd::music_impl            )\
    do_macro(   KeyboardKey             ,   ::dd::keys::kbd_key         )\
    do_macro(   GlyphInfo               ,   ::dd::glyph_info            )\
    do_macro(   Font                    ,   ::dd::font                  )\

//
#define DD_TYPE_CAST(ray_, dd_) \
static inline ray_ cast(const dd_ & val) { return reinterpret_cast< const ray_ & >(val); } \
static inline dd_  cast(const ray_ & val) { return reinterpret_cast< const dd_ & >(val); } \

DD_CAST_TYPES_LIST( DD_TYPE_CAST )

}