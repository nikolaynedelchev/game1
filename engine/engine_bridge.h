#pragma once
//#include "libs.h"
#include <string>
#include <vector>
#include "kbd_bridge.h"

namespace dd
{
struct color
{
    uint8_t r = 0;        // Color red value
    uint8_t g = 0;        // Color green value
    uint8_t b = 0;        // Color blue value
    uint8_t a = 0;        // Color alpha value

    constexpr color() = default;
    constexpr color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : r(r),g(g),b(b),a(a){}
};
    
struct point
{
    float x = 0.0f;
    float y = 0.0f;

    constexpr point() = default;
    constexpr point(float x, float y) : x(x),y(y){}

    void draw(color c, bool bold) const;
};

using vec = point;

// Rectangle, 4 components
struct rect
{
    float x = 0;                // Rectangle top-left corner position x
    float y = 0;                // Rectangle top-left corner position y
    float width = 0;            // Rectangle width
    float height = 0;           // Rectangle height

    constexpr rect() = default;
    constexpr rect(float x, float y, float w, float h) : x(x),y(y),width(w),height(h){}

    void draw(color c, bool filled) const;
};

struct circle
{
    point center;
    float radius = 0.0f;

    constexpr circle() = default;
    constexpr circle(point c, float r) : center(c), radius(r){}
    constexpr circle(float x, float y, float r) : center({x, y}), radius(r){}

    void draw(color, bool filled = false) const;
};

struct transform
{
    vec offset = {0.0f, 0.0f};
    vec scale = {1.0f, 1.0f};
    constexpr transform() = default;
    constexpr transform(dd::vec offset, dd::vec scale) : offset(offset), scale(scale) {}
    constexpr transform(float offset_x, float offset_y, float scale_x, float scale_y) : offset({offset_x, offset_y}), scale({scale_x, scale_y}) {}
};

struct bound
{
    std::vector<rect> rects;
    std::vector<circle> circles;

    void draw(const dd::vec& v) const;
    static bool collision(const dd::bound& b1, const dd::vec& v1,
                          const dd::bound& b2, const dd::vec& v2);
};

struct image
{
    void *data = nullptr;       // Image raw data
    int width = 0;              // Image base width
    int height = 0;             // Image base height
    int mipmaps = 0;            // Mipmap levels, 1 by default
    int format = 0;             // Data format (PixelFormat type)
};

struct texture 
{
    unsigned int id = 0;        // OpenGL texture id
    int width = 0;              // Texture base width
    int height = 0;             // Texture base height
    int mipmaps = 0;            // Mipmap levels, 1 by default
    int format = 0;             // Data format (PixelFormat type)
};

namespace colors
{
    static constexpr color  light_gray{ uint8_t(200), uint8_t(200), uint8_t(200), uint8_t(255) }   ;// Light Gray
    static constexpr color  gray{ 130, 130, 130, 255 }   ;// Gray
    static constexpr color  darkgray{ 80, 80, 80, 255 }      ;// Dark Gray
    constexpr color  yellow      { 253, 249, 0, 255 }     ;// Yellow
    constexpr color  gold        { 255, 203, 0, 255 }     ;// Gold
    constexpr color  orange      { 255, 161, 0, 255 }     ;// Orange
    constexpr color  pink        { 255, 109, 194, 255 }   ;// Pink
    constexpr color  red         { 230, 41, 55, 255 }     ;// Red
    constexpr color  maroon      { 190, 33, 55, 255 }     ;// Maroon
    constexpr color  green       { 0, 228, 48, 255 }      ;// Green
    constexpr color  lime        { 0, 158, 47, 255 }      ;// Lime
    constexpr color  dark_green  { 0, 117, 44, 255 }      ;// Dark Green
    constexpr color  sky_blue    { 102, 191, 255, 255 }   ;// Sky Blue
    constexpr color  blue        { 0, 121, 241, 255 }     ;// Blue
    constexpr color  dark_blue   { 0, 82, 172, 255 }      ;// Dark Blue
    constexpr color  purple      { 200, 122, 255, 255 }   ;// Purple
    constexpr color  violet      { 135, 60, 190, 255 }    ;// Violet
    constexpr color  dark_purple { 112, 31, 126, 255 }    ;// Dark Purple
    constexpr color  beige       { 211, 176, 131, 255 }   ;// Beige
    constexpr color  brown       { 127, 106, 79, 255 }    ;// Brown
    constexpr color  dart_brown  { 76, 63, 47, 255 }      ;// Dark Brown
    constexpr color  white       { 255, 255, 255, 255 }   ;// White
    constexpr color  black       { 0, 0, 0, 255 }         ;// Black
    constexpr color  blank       { 0, 0, 0, 0 }           ;// Blank (Transparent)
    constexpr color  magenta     { 255, 0, 255, 255 }     ;// Magenta
    constexpr color  ray_white   { 245, 245, 245, 255 }   ;// My own White (raylib logo)
}

struct text
{
    std::string symbols;
    point position;
    float size = 0;
    dd::color color = colors::white;
    text() = default;
    text(std::string txt, dd::point pos, float sz, dd::color c) : symbols(std::move(txt)), position(pos), size(sz), color(c){}
};

struct audio_stream
{
    void *buffer;       // Pointer to internal data used by the audio system
    void *processor; // Pointer to internal data processor, useful for audio effects

    unsigned int sample_rate;    // Frequency (samples per second)
    unsigned int sample_size;    // Bit depth (bits per sample): 8, 16, 32 (24 not supported)
    unsigned int channels;      // Number of channels (1-mono, 2-stereo, ...)
};

// Sound
struct sound
{
    audio_stream stream;         // Audio stream
    unsigned int frame_count;    // Total number of frames (considering channels)
};

// Music, audio stream, anything longer than ~10 seconds should be streamed
struct music
{
    audio_stream stream;         // Audio stream
    unsigned int frame_count;    // Total number of frames (considering channels)
    bool looping;               // Music looping enable

    int ctx_type;                // Type of music context (audio filetype)
    void *ctx_data;              // Audio context data, depends on type
};

struct glyph_info
{
    int value;              // Character value (Unicode)
    int offsetX;            // Character offset X when drawing
    int offsetY;            // Character offset Y when drawing
    int advanceX;           // Character advance position X
    dd::image image;            // Character image data
};

struct font 
{
    int default_size;       // Base size (default chars height)
    int glyphs_count;       // Number of glyph characters
    int glyph_padding;      // Padding around the glyph characters
    dd::texture texture;        // Texture atlas containing the glyphs
    dd::rect* recs;             // Rectangles in texture for the glyphs
    dd::glyph_info *glyphs;     // Glyphs info data
};

/////////////////////////////////////////////////////////////////////////////////////

namespace window
{
    void init(int width, int height, const std::string&);  // Initialize window and OpenGL context
    bool should_close();                               // Check if KEY_ESCAPE pressed or Close icon pressed
    void close();
    void set_fullscreen_flag();
    void set_antialiasing_flag();
    void set_vsync_flag();
    void toggle_fullscreen();
}

namespace time
{
    void target_fps(int);
    int target_fps();
    float frame_time();
    double global_time();
}

namespace audio
{
    void init();
    sound load_sound(const std::string& file);
    void play(const sound&);
}

namespace gfx
{
    void begin();
    void end();
    void clear(color);
    void write(const text&);
    void set_font(const std::string& font);
    void set_font_default();
}

namespace kbd
{
    bool key_up(keys::kbd_key k);
    bool key_down(keys::kbd_key k);
    bool key_pressed(keys::kbd_key k);
    bool key_released(keys::kbd_key k);
    void set_exitkey(keys::kbd_key k);
    keys::kbd_key key_pressed();
    int char_pressed();
}

namespace mouse
{
    bool btn_pressed(int button);               // Check if a mouse button has been pressed once
    bool btn_down(int button);                  // Check if a mouse button is being pressed
    bool btn_released(int button);              // Check if a mouse button has been released once
    bool btn_up(int button);                    // Check if a mouse button is NOT being pressed
    int get_x(void);                            // Get mouse position X
    int get_y(void);                            // Get mouse position Y
    point position(void);                       // Get mouse position XY
    vec delta(void);                            // Get mouse delta between frames
    void position(int x, int y);                // Set mouse position XY
    void offset(int offsetX, int offsetY);      // Set mouse offset
    void scale(float scaleX, float scaleY);     // Set mouse scaling
    float wheel_move(void);                     // Get mouse wheel movement for X or Y, whichever is larger
    vec wheel_move_v(void);                     // Get mouse wheel movement for both X and Y
    void cursor_set(int cursor);                // Set mouse cursor
    void cursor_hide();
}

}


// include fmt formatters
#define DD_UNLOCK_FORMATTER_INCLUDE
#include "formatters.hpp"
#undef DD_UNLOCK_FORMATTER_INCLUDE