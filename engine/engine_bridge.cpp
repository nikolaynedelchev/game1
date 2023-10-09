#include "engine_bridge.h"
#include <raylib.h>
#include <raygui.h>
#include "casts.h"
#include <map>
#include "libs.h"

namespace dd
{
    namespace window
    {
        static unsigned s_window_config_flags = 0;
        void init(int width, int height, const string& title)
        {
            SetConfigFlags(s_window_config_flags);
            InitWindow(width, height, title.c_str());
        }

        bool should_close()
        {
            return WindowShouldClose();
        }

        void close()
        {
            return CloseWindow();
        }

        void set_fullscreen_flag()
        {
            s_window_config_flags |= FLAG_FULLSCREEN_MODE;
        }

        void set_antialiasing_flag()
        {
            s_window_config_flags |= FLAG_MSAA_4X_HINT;
        }

        void set_vsync_flag()
        {
            s_window_config_flags |= FLAG_VSYNC_HINT;
        }


        void toggle_fullscreen()
        {
            ToggleFullscreen();
        }
    }

    namespace time
    {
        void target_fps(int fps)
        {
            SetTargetFPS(fps);
        }

        int target_fps()
        {
            return GetFPS();
        }

        float frame_time()
        {
            return GetFrameTime();
        }

        double global_time()
        {
            return GetTime();
        }
    }

    namespace audio
    {
        void init()
        {
            InitAudioDevice();
        }

        ::dd::sound load_sound(const std::string& file)
        {
            return cast(LoadSound(file.c_str()));
        }

        void play(const sound& s)
        {
            PlaySound(cast(s));
        }
    }

    namespace gfx
    {
        void begin()
        {
            BeginDrawing();
        }

        void end()
        {
            EndDrawing();
        }

        void clear(color c)
        {
            ClearBackground(cast(c));
        }

        static map<string, font> s_fonts;
        static bool has_default_font = false;
        static font default_font;

        void write(const ::dd::text& txt)
        {
            if (has_default_font)
            {
                float font_sz = float(default_font.default_size);
                if (txt.size != 0.0f)
                {
                    font_sz = txt.size;
                }
                DrawTextEx(cast(default_font),
                           txt.symbols.c_str(),
                           cast(txt.position),
                           font_sz,
                           1.0f,
                           cast(txt.color)
                           );
            }
            else
            {
                float font_sz = float(GetFontDefault().baseSize);
                if (txt.size != 0.0f)
                {
                    font_sz = txt.size;
                }
                DrawText(txt.symbols.c_str(), 
                        int(txt.position.x),
                        int(txt.position.y),
                        int(font_sz),
                        cast(txt.color));
            }
        }

        void set_font(const std::string& font)
        {
            auto it = s_fonts.find(font);
            if (it == s_fonts.end())
            {
                string file = DD_RSS_FOLDER"/fonts/" + font;
                auto new_font = cast(LoadFont(file.c_str()));
                if (new_font.default_size == 0 ||
                    new_font.glyphs_count == 0 ||
                    new_font.glyphs == nullptr)
                {
                    PrintLn("Error: font not loaded correctly: {}", font);
                }
                else
                {
                    s_fonts[font] = new_font;
                    it = s_fonts.find(font);
                }
            }
            if (it == s_fonts.end())
            {
                PrintLn("Error: font not found: {}", font);
            }
            default_font = it->second;
            has_default_font = true;
        }

        void set_font_default()
        {
            has_default_font = false;
        }
    }

    namespace kbd
    {
        bool key_up(keys::kbd_key k)
        {
            return IsKeyUp(cast(k));
        }

        bool key_down(keys::kbd_key k)
        {
            return IsKeyDown(cast(k));
        }

        bool key_pressed(keys::kbd_key k)
        {
            return IsKeyPressed(cast(k));
        }

        bool key_released(keys::kbd_key k)
        {
            return IsKeyReleased(cast(k));
        }

        void set_exitkey(keys::kbd_key k)
        {
            SetExitKey(cast(k));
        }

        keys::kbd_key key_pressed()
        {
            return cast(KeyboardKey(GetKeyPressed()));
        }

        int char_pressed()
        {
            return GetCharPressed();
        }
    }

    namespace mouse
    {
        bool btn_pressed(int button)
        {
            return IsMouseButtonPressed(button);
        }

        bool btn_down(int button)
        {
            return IsMouseButtonDown(button);
        }

        bool btn_released(int button)
        {
            return IsMouseButtonReleased(button);
        }

        bool btn_up(int button)
        {
            return IsMouseButtonUp(button);
        }

        int get_x(void)
        {
            return GetMouseX();
        }

        int get_y(void)
        {
            return GetMouseY();
        }

        point position(void)
        {
            return cast(GetMousePosition());
        }

        vec delta(void)
        {
            return cast(GetMouseDelta());
        }

        void position(int x, int y)
        {
            SetMousePosition(x, y);
        }

        void offset(int offsetX, int offsetY)
        {
            SetMouseOffset(offsetX, offsetY);
        }

        void scale(float scaleX, float scaleY)
        {
            SetMouseScale(scaleX, scaleY);
        }

        float wheel_move(void)
        {
            return GetMouseWheelMove();
        }

        vec wheel_move_v(void)
        {
            return cast(GetMouseWheelMoveV());
        }

        void cursor_set(int cursor)
        {
            SetMouseCursor(cursor);
        }

        void cursor_hide()
        {
            HideCursor();
        }
    }

}