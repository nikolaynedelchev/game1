﻿#include "engine_bridge.h"
#include "casts.h"
#include <map>
#include "libs.h"

#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#undef RAYGUI_IMPLEMENTATION

#include "operators.h"
#include "formatters.hpp"

namespace dd
{
    static std::string rss_folder_;
    void rss_folder(std::string folder)
    {
        rss_folder_ = std::move(folder);
    }
    const std::string& rss_folder()
    {
        return rss_folder_;
    }

    void point::draw(color c, bool bold) const
    {
        if (bold)
        {
            DrawCircle(int(this->x), int(this->y), 3.0f, cast(c));
        }
        else
        {
            DrawPixel(int(this->x), int(this->y), cast(c));
        }
    }

    point rect::position() const
    {
        return {x, y};
    }

    vec rect::size() const
    {
        return {width, height};
    }

    void rect::position(dd::point p)
    {
        this->x = p.x;
        this->y = p.y;
    }

    void rect::size(dd::vec s)
    {
        this->width = s.x;
        this->height = s.y;
    }

    dd::rect rect::bounding_rect(int spacing) const
    {
        dd::rect b = *this;
        b.x -= spacing;
        b.y -= spacing;
        b.width += 2*spacing;
        b.height += 2*spacing;
        return b;
    }

    void rect::draw(color c, bool filled) const
    {
        if (filled)
        {
            DrawRectangle(int(this->x), int(this->y), int(this->width), int(this->height), cast(c));
        }
        else
        {
            DrawRectangleLines(int(this->x), int(this->y), int(this->width), int(this->height), cast(c));
        }
    }

    dd::point rect::anchor(anchors a) const
    {
        dd::point res;
        switch (a)
        {
        case dd::anchors::up_left:      return this->position();
        case dd::anchors::up_mid:       return this->position() + dd::vec(this->width / 2.0f, 0.0f);
        case dd::anchors::up_right:     return this->position() + dd::vec(this->width, 0.0f);
        case dd::anchors::mid_left:     return this->position() + dd::vec(0.0f, this->height / 2.0f);
        case dd::anchors::centered:     return this->position() + dd::vec(this->width / 2.0f, this->height / 2.0f);
        case dd::anchors::mid_right:    return this->position() + dd::vec(this->width, this->height / 2.0f);
        case dd::anchors::down_left:    return this->position() + dd::vec(0.0f, this->height);
        case dd::anchors::down_mid:     return this->position() + dd::vec(this->width / 2.0f, this->height);
        case dd::anchors::down_right:   return this->position() + dd::vec(this->width, this->height);
        default: break;
        }
        return dd::point();
    }



    // namespace window
    // {
        static unsigned s_window_config_flags = 0;
        void engine::init(std::string game_folder, 
                          int width, int height, 
                          const std::string& window_title,
                          bool fullscreen)
        {
            rss_folder(game_folder);
            s_window_config_flags |= FLAG_MSAA_4X_HINT;
            s_window_config_flags |= FLAG_VSYNC_HINT;
            if (fullscreen)
            {
                s_window_config_flags |= FLAG_FULLSCREEN_MODE;
            }
            else
            {
                s_window_config_flags |= FLAG_WINDOW_RESIZABLE;
            }
            SetConfigFlags(s_window_config_flags);
            auto title = window_title;
            if (title.empty())
            {
                title = game_folder;
            }
            InitWindow(width, height, window_title.c_str());

            InitAudioDevice();
        }

        bool engine::should_close()
        {
            return WindowShouldClose();
        }

        void engine::close()
        {
            return CloseWindow();
        }

        void engine::toggle_fullscreen_win()
        {
            ToggleFullscreen();
        }
    // }

    // namespace time
    // {
        void engine::target_fps(int fps)
        {
            SetTargetFPS(fps);
        }

        int engine::target_fps()
        {
            return GetFPS();
        }

        float engine::frame_time()
        {
            return GetFrameTime();
        }

        double engine::global_time()
        {
            return GetTime();
        }
    // }

        void engine::begin_frame()
        {
            BeginDrawing();
        }

        void engine::end_frame()
        {
            EndDrawing();
        }

        void engine::clear_frame(color c)
        {
            ClearBackground(cast(c));
        }

        bool engine::key_up(keys::kbd_key k)
        {
            return IsKeyUp(cast(k));
        }

        bool engine::key_down(keys::kbd_key k)
        {
            return IsKeyDown(cast(k));
        }

        bool engine::key_pressed(keys::kbd_key k)
        {
            return IsKeyPressed(cast(k));
        }

        bool engine::key_released(keys::kbd_key k)
        {
            return IsKeyReleased(cast(k));
        }

        void engine::set_exitkey(keys::kbd_key k)
        {
            SetExitKey(cast(k));
        }

        keys::kbd_key engine::key_pressed()
        {
            return cast(KeyboardKey(GetKeyPressed()));
        }

        int engine::char_pressed()
        {
            return GetCharPressed();
        }

        bool engine::mouse_btn_pressed(int button)
        {
            return IsMouseButtonPressed(button);
        }

        bool engine::mouse_btn_down(int button)
        {
            return IsMouseButtonDown(button);
        }

        bool engine::mouse_btn_released(int button)
        {
            return IsMouseButtonReleased(button);
        }

        bool engine::mouse_btn_up(int button)
        {
            return IsMouseButtonUp(button);
        }

        int engine::mouse_x(void)
        {
            return GetMouseX();
        }

        int engine::mouse_y(void)
        {
            return GetMouseY();
        }

        point engine::mouse_position(void)
        {
            return cast(GetMousePosition());
        }

        vec engine::mouse_delta(void)
        {
            return cast(GetMouseDelta());
        }

        void engine::mouse_position(int x, int y)
        {
            SetMousePosition(x, y);
        }

        void engine::mouse_offset(int offsetX, int offsetY)
        {
            SetMouseOffset(offsetX, offsetY);
        }

        void engine::mouse_scale(float scaleX, float scaleY)
        {
            SetMouseScale(scaleX, scaleY);
        }

        float engine::mouse_wheel_move(void)
        {
            return GetMouseWheelMove();
        }

        vec engine::mouse_wheel_move_v(void)
        {
            return cast(GetMouseWheelMoveV());
        }

        void engine::mouse_cursor_set(int cursor)
        {
            SetMouseCursor(cursor);
        }

        void engine::mouse_cursor_hide()
        {
            HideCursor();
        }

}