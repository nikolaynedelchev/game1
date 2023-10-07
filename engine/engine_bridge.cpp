#include "engine_bridge.h"
#include <raylib.h>
#include <raygui.h>
#include "casts.h"


namespace dd
{
    namespace window
    {
        void init(int width, int height, const string& title)
        {
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
            SetConfigFlags(FLAG_FULLSCREEN_MODE);
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

        void write(const ::dd::text& txt)
        {
            DrawText(txt.symbols.c_str(), 
                    int(txt.position.x),
                    int(txt.position.y),
                    txt.size,
                    cast(txt.color));
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