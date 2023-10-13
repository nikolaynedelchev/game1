#include "engine_ex.h"
#include <raylib.h>
#include "casts.h"
#include "operators.h"
#include "formatters.hpp"

namespace dd
{


void circle::draw(color color, bool filled) const
{
    if (filled)
    {
        DrawCircle(int(center.x),
                int(center.y),
                radius, cast(color));
    }
    else
    {
        DrawCircleLines(int(center.x),
                        int(center.y),
                        radius, cast(color));
    }
}

bool bound::collision(const bound &b1, const vec &v1, const bound &b2, const vec &v2)
{
    for(const auto& r1 : b1.rects)
    {
        for(const auto& r2 : b2.rects)
        {
            if (CheckCollisionRecs(cast(r1 + v1), cast(r2 + v2)))
            {
                return true;
            }
        }
        for(const auto& c2 : b2.circles)
        {
            if (CheckCollisionCircleRec(cast(c2.center + v2), c2.radius, cast(r1 + v1)))
            {
                return true;
            }
        }
    }
    for(const auto& c1 : b1.circles)
    {
        for(const auto& r2 : b2.rects)
        {
            if (CheckCollisionCircleRec(cast(c1.center + v1), c1.radius, cast(r2 + v2)))
            {
                return true;
            }
        }
        for(const auto& c2 : b2.circles)
        {
            if (CheckCollisionCircles(cast(c1.center + v1), c1.radius,
                                    cast(c2.center + v2), c2.radius))
            {
                return true;
            }
        }
    }
    return false;
}

void bound::draw(const vec &v) const
{
    for(const auto& r : rects)
    {
        (r+v).draw(colors::white, false);
    }
    for(auto c : circles)
    {
        (c+v).draw(colors::white, false);
    }
}


static map<string, uint32_t> s_ids;
static vector<texture> s_textures;

static bool create(const string& imageFile)
{
    if (s_ids.find(imageFile) != s_ids.end())
    {
        return true;
    }

    string fullFileName = DD_RSS_FOLDER"/images/" + imageFile;
    Image image = LoadImage(fullFileName.c_str());
    if (image.data == nullptr)
    {
        PrintLn("Error: Empty image: key: {} , full: {}", imageFile, fullFileName);
        return false;
    }
    Texture2D texture = LoadTextureFromImage(image);
    if (texture.id == 0)
    {
        UnloadImage(image);
        PrintLn("Error: Texture construct failed: key: {} , full: {}", imageFile, fullFileName);
        return false;
    }
    s_ids[imageFile] = s_textures.size();
    s_textures.push_back(cast(texture));
    UnloadImage(image);
    return true;
}

sprite sprite::load(const string& imageFile, 
                    rect source,
                    transform targetTransform)
{
    auto id_it = s_ids.find(imageFile);
    if (id_it == s_ids.end())
    {
        if (create(imageFile) == false)
        {
            FatalError("Faild to create texture: {}", imageFile);
            return sprite();
        }
        id_it = s_ids.find(imageFile);
        if (id_it == s_ids.end())
        {
            FatalError("Error: CreateTexture unknown failier: {}", imageFile);
            return sprite();
        }
    }
    sprite sprite;
    sprite.texture_id = id_it->second;
    texture texture = s_textures[sprite.texture_id];
    sprite.rotate = 0.0f;
    sprite.source = source;
    if (sprite.source.width == 0.0f && sprite.source.height == 0.0f)
    {
        sprite.source.width = float(texture.width);
        sprite.source.height = float(texture.height);
    }

    // TODO: experimental flip
    //sprite.source.x = sprite.source.width; // not correct
    //sprite.source.width = -sprite.source.width;

    sprite.target = targetTransform;
    sprite.position = {0.0f, 0.0f};
    sprite.visible = true;
    sprite.loaded = true;
    return sprite;
}

void sprite::release_spritres()
{
    for(auto& t : s_textures)
    {
        UnloadTexture(cast(t));   
    }
    s_textures.clear();
    s_ids.clear();
}

static inline rect get_dest_rect(const sprite& sprite)
{
    return (dd::rect{0.0f, 0.0f, sprite.source.width, sprite.source.height} * sprite.target) + sprite.position;
}

static inline point get_origin(const sprite& sprite)
{
    return (point{sprite.source.width, sprite.source.height} * sprite.target.scale) / 2.0f;
}

void sprite::draw() const
{
    if (loaded == false ||
        visible == false)
    {
        return;
    }

    auto src = source;
    if (flip_x) src.width = -src.width;
    if (flip_y) src.height = -src.height;

    DrawTexturePro(cast(s_textures[ texture_id ]), 
                   cast(src),
                   cast(get_dest_rect(*this)),
                   cast(get_origin(*this)),
                   0.0f,
                   WHITE);
}

point sprite::global_pos() const
{
    return (point{0.0f, 0.0f} * target) + position;
}

rect sprite::global_rect() const
{
    auto dest_rect = get_dest_rect(*this);
    auto origin = get_origin(*this);
    dest_rect.x -= origin.x;
    dest_rect.y -= origin.y;
    return dest_rect;
}

rect sprite::origin_rect() const
{
    auto g_rect = global_rect();
    auto g_pos = global_pos();
    g_rect.x -= g_pos.x;
    g_rect.y -= g_pos.y;
    return g_rect;
}


bool sprite::collision(const dd::sprite& s2) const
{
    return bound::collision(bound, global_pos(), s2.bound, s2.global_pos());
}



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
        frame_sprite.draw();
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