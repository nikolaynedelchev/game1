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

    int frame(const anim& a)
    {
        if (a.visible == false ||
            a.privates.frames.empty())
        {
            return -1;
        }
        int f = size_t( progress(a) * float(a.privates.frames.size()) );
        if (f >= int(a.privates.frames.size()))
        {
            f = a.privates.frames.size() - 1;
        }
        return f;
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
        auto frame = gfx::frame(a);
        if (frame < 0)
        {
            return;
        }

        auto frame_sprite = a.privates.frames[size_t(frame)];

        frame_sprite.position = a.position;
        frame_sprite.target = a.target;
        frame_sprite.rotate = a.rotate;
        frame_sprite.flip_x = a.flip_x;
        frame_sprite.flip_y = a.flip_y;
        draw(frame_sprite);
    }

    bool collision(const dd::anim& a1, const dd::anim& a2)
    {
        auto f1 = frame(a1);
        if (f1 < 0)
        {
            return false;
        }
        auto f2 = frame(a2);
        if (f2 < 0)
        {
            return false;
        }
        return collision(a1.privates.frames[f1].bound, a1.privates.frames[f1].position + a1.position,
                         a2.privates.frames[f2].bound, a2.privates.frames[f2].position + a2.position);
    }

    bool collision(const dd::anim& a1, const dd::sprite& s2)
    {
        auto f1 = frame(a1);
        if (f1 < 0)
        {
            return false;
        }
        return collision(a1.privates.frames[f1].bound, a1.privates.frames[f1].position + a1.position,
                         s2.bound, s2.position);
    }

}
}