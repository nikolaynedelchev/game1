#include "anim.h"

namespace dd
{

    void anim::fps(float fps)
    {
        if (p_.fps == 0.0f)
        {
            p_.fps = fps;
            restart();
            return;
        }
        auto current_progress = progress();
        p_.fps = fps;
        p_.elapsed = duration() * current_progress;
    }

    float anim::fps() const
    {
        return p_.fps;
    }

    void anim::add_frame(sprite s)
    {
        p_.frames.push_back(std::move(s));
    }

    void anim::play()
    {
        restart();
        pause(false);
    }

    void anim::pause(bool paused)
    {
        p_.paused = paused;
    }

    void anim::restart()
    {
        p_.elapsed = -1.0f;
    }

    bool anim::paused() const
    {
        return p_.paused;
    }

    bool anim::finished() const
    {
        if (loop)
        {
            return false;
        }
        return p_.elapsed >= duration();
    }

    float anim::duration() const
    {
        if (p_.fps == 0.0f)
        {
            return 0.0f;
        }
        return float(p_.frames.size()) / p_.fps;
    }

    float anim::progress() const
    {
        return p_.elapsed / duration();
    }

    float anim::elapsed() const
    {
        return p_.elapsed;
    }

    int anim::frame() const
    {
        if (visible == false ||
            p_.frames.empty())
        {
            return -1;
        }
        int f = size_t( progress() * float(p_.frames.size()) );
        if (f >= int(p_.frames.size()))
        {
            f = p_.frames.size() - 1;
        }
        return f;
    }

    void anim::update()
    {
        if (p_.paused ||
            p_.fps == 0 || 
            p_.frames.empty())
        {
            return;
        }

        auto dur = duration();
        if (p_.elapsed < 0.0f)
        {
            p_.elapsed = 0.0f;
        }
        else
        {
            if (loop || p_.elapsed <= dur)
            {
                p_.elapsed += time::frame_time();
            }
        }

        if (loop)
        {
            while(p_.elapsed >= dur)
            {
                p_.elapsed -= dur;
            }
            if (p_.elapsed < 0.0f)
            {
                p_.elapsed = 0.0f;
            }
        }

    }

    void anim::draw() const
    {
        auto fr = frame();
        if (fr < 0)
        {
            return;
        }

        auto frame_sprite = p_.frames[size_t(fr)];

        frame_sprite.position = position;
        frame_sprite.target = target;
        frame_sprite.rotate = rotate;
        frame_sprite.flip_x = flip_x;
        frame_sprite.flip_y = flip_y;
        gfx::draw(frame_sprite);
    }

    bool anim::collision(const dd::anim& a2) const
    {
        auto f1 = frame();
        if (f1 < 0)
        {
            return false;
        }
        auto f2 = a2.frame();
        if (f2 < 0)
        {
            return false;
        }
        return bound::collision(p_.frames[f1].bound, p_.frames[f1].position + position,
                                a2.p_.frames[f2].bound, a2.p_.frames[f2].position + a2.position);
    }

    bool anim::collision(const dd::sprite& s2) const
    {
        auto f1 = frame();
        if (f1 < 0)
        {
            return false;
        }
        return bound::collision(p_.frames[f1].bound, p_.frames[f1].position + position,
                                s2.bound, s2.position);
    }
}