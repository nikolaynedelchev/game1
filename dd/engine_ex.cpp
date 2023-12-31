﻿#include "engine_ex.h"
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
        DrawCircle(int(this->center.x),
                   int(this->center.y),
                   this->radius, cast(color));
    }
    else
    {
        DrawCircleLines(int(this->center.x),
                        int(this->center.y),
                        this->radius, cast(color));
    }
}

bool bound::collision(const bound &b1, const vec &v1,
                      const bound& b2, const vec& v2)
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

bool bound::collision(const bound& b1, const vec& v1,
                      const rect& r2)
{
    bound b2;
    b2.rects.push_back(r2);
    return collision(b1, v1, b2, {});
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

static std::map<std::string, uint32_t> s_ids;
static std::vector<texture> s_textures;

static bool create(const std::string& imageFile)
{
    if (s_ids.find(imageFile) != s_ids.end())
    {
        return true;
    }

    std::string fullFileName = rss_folder() + "/images/" + imageFile;
    Image image = LoadImage(fullFileName.c_str());
    if (image.data == nullptr)
    {
        println("Error: Empty image: key: {} , full: {}", imageFile, fullFileName);
        return false;
    }
    Texture2D texture = LoadTextureFromImage(image);
    if (texture.id == 0)
    {
        UnloadImage(image);
        println("Error: Texture construct failed: key: {} , full: {}", imageFile, fullFileName);
        return false;
    }
    s_ids[imageFile] = uint32_t(s_textures.size());
    s_textures.push_back(cast(texture));
    UnloadImage(image);
    return true;
}

/*

RLAPI void BeginTextureMode(RenderTexture2D target);              // Begin drawing to render texture
RLAPI void EndTextureMode(void);

*/
void sprite::load(const std::string& imageFile, 
                  dd::rect src,
                  dd::vec sz)
{
    auto id_it = s_ids.find(imageFile);
    if (id_it == s_ids.end())
    {
        if (create(imageFile) == false)
        {
            fatal_error("Faild to create texture: {}", imageFile);
            *this = sprite();
            return;
        }
        id_it = s_ids.find(imageFile);
        if (id_it == s_ids.end())
        {
            fatal_error("Error: CreateTexture unknown failier: {}", imageFile);
            *this = sprite();
            return;
        }
    }
    this->texture_id = id_it->second;
    dd::texture texture = s_textures[texture_id];
    this->rotate = 0.0f;
    this->source = src;
    if (this->source.size() == dd::vec(0, 0))
    {
        this->source.width = float(texture.width);
        this->source.height = float(texture.height);
    }

    this->size = sz;
    if (this->size == dd::vec(0, 0))
    {
        this->size = this->source.size();
    }
    this->position = {0.0f, 0.0f};
    this->visible = true;
    this->loaded = true;
}

void sprite::attach(sprite s, point offset)
{
    auto sprite_ptr = std::make_shared<sprite>();
    *sprite_ptr = std::move(s);
    attached.push_back({sprite_ptr, offset});
}

dd::rect sprite::rect() const
{
    return dd::rect(this->position, this->size).anchor_rect(anchor);
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

void sprite::update()
{
    update_attached();
}

void sprite::draw() const
{
    if (this->loaded == false ||
        this->visible == false)
    {
        return;
    }

    auto src = this->source;
    if (flip_x) src.width = -src.width;
    if (flip_y) src.height = -src.height;
    vec anchor_pos = dd::rect({0.0f, 0.0f}, this->size).anchor_pos(this->anchor);

    DrawTexturePro(cast(s_textures[ this->texture_id ]), 
                   cast(src),
                   cast(dd::rect(this->position, this->size)),
                   cast(anchor_pos),
                   this->rotate,
                   WHITE);

    for(const auto& a : attached)
    {
        a.sprite_ptr->draw_at(position + a.offset_pos, anchor);
    }
}

void sprite::draw_at(point pos, anchors anchor) const
{
    if (this->loaded == false ||
        this->visible == false)
    {
        return;
    }

    auto src = this->source;
    if (flip_x) src.width = -src.width;
    if (flip_y) src.height = -src.height;
    vec anchor_pos = dd::rect(dd::point(0.0f, 0.0f), this->size).anchor_pos(anchor);

    DrawTexturePro(cast(s_textures[ this->texture_id ]),
                   cast(src),
                   cast(dd::rect(pos, this->size)),
                   cast(anchor_pos),
                   this->rotate,
                   WHITE);

    for(const auto& a : attached)
    {
        a.sprite_ptr->draw_at(pos + a.offset_pos, anchor);
    }
}

bool sprite::collision(const sprite &s1, const sprite &s2)
{
    if (collision(s1, "", s2, ""))
    {
        return true;
    }
    for(const auto& a1 : s1.attached)
    {
        for(const auto& a2 : s2.attached)
        {
            if (collision(*a1.sprite_ptr, "", *a2.sprite_ptr, ""))
            {
                return true;
            }
        }
    }
    for(const auto& a1 : s1.attached)
    {
        if (collision(*a1.sprite_ptr, "", s2, ""))
        {
            return true;
        }
    }
    for(const auto& a2 : s2.attached)
    {
        if (collision(*a2.sprite_ptr, "", s1, ""))
        {
            return true;
        }
    }
    return false;
}

bool sprite::collision(const sprite& s1, const std::string& boundName1,
                       const sprite& s2, const std::string& boundName2)
{
    auto it1 = s1.bounds.find(boundName1);
    auto it2 = s2.bounds.find(boundName2);

    if (it1 != s1.bounds.end() && it2 != s2.bounds.end())
    {
        if (bound::collision(it1->second, s1.rect().position(),
                             it2->second, s2.rect().position()))
        {
            return true;
        }
    }

    for(const auto& a1 : s1.attached)
    {
        auto it1 = a1.sprite_ptr->bounds.find(boundName1);
        if (it1 != a1.sprite_ptr->bounds.end())
        {
            for(const auto& a2 : s2.attached)
            {
                auto it2 = a2.sprite_ptr->bounds.find(boundName2);
                if (it2 != a2.sprite_ptr->bounds.end())
                {
                    if (bound::collision(it1->second, s1.rect().position() + a1.offset_pos,
                                         it2->second, s2.rect().position() + a2.offset_pos))
                    {
                        return true;
                    }
                }
            }
        }
    }
    if (it2 != s2.bounds.end())
    {
        for(const auto& a1 : s1.attached)
        {
            auto it1 = a1.sprite_ptr->bounds.find(boundName1);
            if (it1 != a1.sprite_ptr->bounds.end())
            {
                if (bound::collision(it1->second, s1.rect().position() + a1.offset_pos,
                                     it2->second, s2.rect().position()))
                {
                    return true;
                }
            }
        }
    }
    if (it1 != s1.bounds.end())
    {
        for(const auto& a2 : s2.attached)
        {
            auto it2 = a2.sprite_ptr->bounds.find(boundName2);
            if (it2 != a2.sprite_ptr->bounds.end())
            {
                if (bound::collision(it1->second, s1.rect().position(),
                                     it2->second, s2.rect().position() + a2.offset_pos))
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool sprite::collision(const sprite& s1, const std::string& boundName1,
                       const dd::rect& r2)
{
    auto it1 = s1.bounds.find(boundName1);
    if (it1 != s1.bounds.end())
    {
        if (bound::collision(it1->second, s1.rect().position(), r2))
        {
            return true;
        }
    }

    for(const auto& a1 : s1.attached)
    {
        auto it1 = a1.sprite_ptr->bounds.find(boundName1);
        if (it1 != a1.sprite_ptr->bounds.end())
        {
            if (bound::collision(it1->second, s1.rect().position() + a1.offset_pos, r2))
            {
                return true;
            }
        }
    }
    return false;
}

void sprite::update_attached()
{
    for(auto& a : attached)
    {
        a.sprite_ptr->position = position + a.offset_pos;
        a.sprite_ptr->anchor = anchor;
    }
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
    s.visible = true;
    p_.frames.push_back(std::move(s));
    if (s.size.x > this->size.x) this->size.x = s.size.x;
    if (s.size.y > this->size.y) this->size.y = s.size.y;
}

void anim::play()
{
    restart();
    pause(false);
}

void anim::pause(bool paused)
{
    p_.paused = paused;
    update(true);
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
    int f = int( progress() * float(p_.frames.size()) );
    if (f >= int(p_.frames.size()))
    {
        f = int(p_.frames.size()) - 1;
    }
    return f;
}

void anim::update(bool firstFrame)
{
    auto setup_frame = [this](){
        auto fr = this->frame();
        if (fr < 0)
        {
            return;
        }

        auto& frame_sprite = p_.frames[size_t(fr)];

        frame_sprite.position = this->position;
        frame_sprite.anchor = this->anchor;
        frame_sprite.rotate = this->rotate;
        frame_sprite.flip_x = this->flip_x;
        frame_sprite.flip_y = this->flip_y;
        frame_sprite.update();
    };
    if (p_.paused ||
        p_.fps == 0 ||
        p_.frames.empty())
    {
        setup_frame();
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
            p_.elapsed += firstFrame ? 0.0f : GetFrameTime();
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
    setup_frame();
}

void anim::draw()
{
    auto fr = this->frame();
    if (fr < 0)
    {
        return;
    }

    const auto& frame_sprite = p_.frames[size_t(fr)];

//    frame_sprite.position = this->position;
//    frame_sprite.anchor = this->anchor;
//    frame_sprite.size = this->size;
//    frame_sprite.rotate = this->rotate;
//    frame_sprite.flip_x = this->flip_x;
//    frame_sprite.flip_y = this->flip_y;
    frame_sprite.draw();
}

rect anim::rect() const
{
    auto f = this->frame();
    if (f < 0)
    {
        return {0.0f, 0.0f, 0.0f, 0.0f};
    }
    return this->p_.frames[f].rect();// + position;
}

bool anim::collision(const anim &a1, const anim &a2)
{
    return collision(a1, "", a2, "");
}

bool anim::collision(const anim &a1, const sprite &s2)
{
    return collision(a1, "", s2, "");
}

bool anim::collision(const anim& a1, const std::string& boundName1,
                      const anim& a2, const std::string& boundName2)
{
    auto f1 = a1.frame();
    if (f1 < 0)
    {
        return false;
    }
    auto f2 = a2.frame();
    if (f2 < 0)
    {
        return false;
    }

    return sprite::collision(a1.p_.frames[f1], boundName1,
                             a2.p_.frames[f2], boundName2);
}

bool anim::collision(const anim& a1, const std::string& boundName1,
                      const sprite& s2, const std::string& boundName2)
{
    auto f1 = a1.frame();
    if (f1 < 0)
    {
        return false;
    }

    return sprite::collision(a1.p_.frames[f1], boundName1,
                             s2, boundName2);
}

void sound::load(const std::string& file)
{
    std::string full_name = rss_folder() + "/sounds/" + file;
//    if (file == "jump.wav")
//    {
//        Wave w = LoadWave(full_name.c_str());
//        int from = 4500;
//        int to = 33074;
//        WaveCrop(&w, from, to);
//        w.frameCount = (to - from) / w.channels;
//        ExportWave(w, "exported_jump.wav");
//        p_.sound_ = cast(LoadSoundFromWave(w));
//    }
//    else
    {
        p_.sound_ = cast(LoadSound(full_name.c_str()));
    }
}

void sound::play()
{
    PlaySound(cast(p_.sound_));
}

void sound::stop()
{
    StopSound(cast(p_.sound_));
}

bool sound::is_playing() const
{
    return IsSoundPlaying(cast(p_.sound_));
}

void sound::volume(float v)
{
    SetSoundVolume(cast(p_.sound_), v);
}

dd::vec text::size() const
{
    if (p_.has_default_font)
    {
        return
        cast
        (
            MeasureTextEx(cast(p_.text_font),
                          symbols.c_str(),
                          font_size==0.0f?p_.text_font.default_size:font_size,
                          1.0f)
        );
    }
    else
    {
        return {0, 0};
//            cast
//            (
//                MeasureText(symbols.c_str(),
//                            font_size==0.0f?GetFontDefault().baseSize:int(font_size))
//            );
    }
}

rect text::rect() const
{
    auto pos = position;
    auto sz = size();
    if (anchor != anchors::up_left)
    {
        dd::rect r = {{0, 0}, sz};
        dd::point p = r.anchor_pos(anchor);
        pos = pos - p;
    }
    return {pos, sz};
}

static std::map<std::string, font> s_fonts;
void text::draw() const
{
    if (p_.has_default_font)
    {
        auto pos = position;
        if (anchor != anchors::up_left)
        {
            dd::rect r = {{0, 0}, size()};
            dd::point p = r.anchor_pos(anchor);
            pos = pos - p;
        }
        DrawTextEx(cast(p_.text_font),
                   symbols.c_str(),
                   cast(pos),
                   font_size==0.0f?p_.text_font.default_size:font_size,
                   1.0f,
                   cast(color));
    }
    else
    {
        DrawText(symbols.c_str(),
                 int(position.x),
                 int(position.y),
                 font_size==0.0f?GetFontDefault().baseSize:font_size,
                cast(color));
    }
}

void text::clear_background(dd::color color) const
{
    dd::rect(this->position, this->size()).bounding_rect().draw(color, true);
}

void text::set_font(const std::string& font)
{
    auto it = s_fonts.find(font);
    if (it == s_fonts.end())
    {
        std::string file = rss_folder() + "/fonts/" + font;
        auto new_font = cast(LoadFont(file.c_str()));
        if (new_font.default_size == 0 ||
            new_font.glyphs_count == 0 ||
            new_font.glyphs == nullptr)
        {
            println("Error: font not loaded correctly: {}", font);
        }
        else
        {
            s_fonts[font] = new_font;
            it = s_fonts.find(font);
        }
    }
    if (it == s_fonts.end())
    {
        println("Error: font not found: {}", font);
    }
    p_.text_font = it->second;
    p_.has_default_font = true;
}

void text::set_font_default()
{
    p_.has_default_font = false;
}

}
