#include "anim.h"

namespace dd
{
namespace gfx
{
    void fps(anim& a, float fps)
    {
        if (a.privates.fps == 0.0f)
        {
            a.privates.fps = fps;
            restart(a);
            return;
        }
        auto current_progress = progress(a);
        a.privates.fps = fps;
        a.privates.elapsed = duration(a) * current_progress;
    }

    float fps(const anim& a)
    {
        return a.privates.fps;
    }

    void add_frame(anim& a, sprite s)
    {
        a.privates.frames.push_back(std::move(s));
    }

    void play(anim& a)
    {
        restart(a);
        pause(a, false);
    }

    void pause(anim& a, bool paused)
    {
        a.privates.paused = paused;
    }

    void restart(anim& a)
    {
        a.privates.elapsed = -1.0f;
    }

    bool paused(const anim& a)
    {
        return a.privates.paused;
    }

    bool finished(const anim& a)
    {
        if (a.loop)
        {
            return false;
        }
        return a.privates.elapsed >= duration(a);
    }

    float duration(const anim& a)
    {
        if (a.privates.fps == 0.0f)
        {
            return 0.0f;
        }
        return float(a.privates.frames.size()) / a.privates.fps;
    }

    float progress(const anim& a)
    {
        return a.privates.elapsed / duration(a);
    }

    float elapsed(const anim& a)
    {
        return a.privates.elapsed;
    }

    void update(anim& a)
    {
        if (a.privates.paused ||
            a.privates.fps == 0 || 
            a.privates.frames.empty())
        {
            return;
        }

        auto duration = gfx::duration(a);
        if (a.privates.elapsed < 0.0f)
        {
            a.privates.elapsed = 0.0f;
        }
        else
        {
            if (a.loop || a.privates.elapsed <= duration)
            {
                a.privates.elapsed += time::frame_time();
            }
        }

        if (a.loop)
        {
            while(a.privates.elapsed >= duration)
            {
                a.privates.elapsed -= duration;
            }
            if (a.privates.elapsed < 0.0f)
            {
                a.privates.elapsed = 0.0f;
            }
        }

    }

    void draw(const anim& a)
    {
        if (a.privates.paused)
        {
            return;
        }
        size_t f = size_t( progress(a) * float(a.privates.frames.size()) );
        if (f >= a.privates.frames.size())
        {
            return;
        }

        auto frame_sprite = a.privates.frames[f];

        frame_sprite.position = a.position;
        frame_sprite.target = a.target;
        frame_sprite.rotate = a.rotate;
        frame_sprite.flip_x = a.flip_x;
        frame_sprite.flip_y = a.flip_y;
        draw(frame_sprite);
    }
}
}