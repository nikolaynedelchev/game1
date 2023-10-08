#pragma once
//#include "libs.h"
#include <string>
#include "kbd_bridge.h"
using namespace std;

namespace dd
{
    
struct point
{
    float x = 0.0f;
    float y = 0.0f;
};

using vec = point;

// Rectangle, 4 components
struct rect
{
    float x = 0;                // Rectangle top-left corner position x
    float y = 0;                // Rectangle top-left corner position y
    float width = 0;            // Rectangle width
    float height = 0;           // Rectangle height
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

struct color
{
    unsigned char r = 0;        // Color red value
    unsigned char g = 0;        // Color green value
    unsigned char b = 0;        // Color blue value
    unsigned char a = 0;        // Color alpha value
};

namespace colors
{
    constexpr color  light_gray  { 200, 200, 200, 255 }   ;// Light Gray
    constexpr color  gray        { 130, 130, 130, 255 }   ;// Gray
    constexpr color  darkgray    { 80, 80, 80, 255 }      ;// Dark Gray
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
    string symbols;
    point position;
    float size = 0;
    color color = colors::white;
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
    image image;            // Character image data
};

struct font 
{
    int default_size;       // Base size (default chars height)
    int glyphs_count;       // Number of glyph characters
    int glyph_padding;      // Padding around the glyph characters
    texture texture;        // Texture atlas containing the glyphs
    rect* recs;             // Rectangles in texture for the glyphs
    glyph_info *glyphs;     // Glyphs info data
};

/////////////////////////////////////////////////////////////////////////////////////

namespace window
{
    void init(int width, int height, const string&);  // Initialize window and OpenGL context
    bool should_close();                               // Check if KEY_ESCAPE pressed or Close icon pressed
    void close();
    void set_fullscreen_flag();
    void set_antialiasing_flag();
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