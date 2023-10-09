#include "sprite.h"
#include "casts.h"
#include "shapes.h"
namespace dd
{
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

namespace gfx
{
    sprite load_sprite(const string& imageFile, 
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

    void release_spritres()
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

    void draw(const sprite& sprite)
    {
        if (sprite.loaded == false ||
            sprite.visible == false)
        {
            return;
        }

        auto src = sprite.source;
        if (sprite.flip_x) src.width = -src.width;
        if (sprite.flip_y) src.height = -src.height;

        DrawTexturePro(cast(s_textures[ sprite.texture_id ]), 
                       cast(src),
                       cast(get_dest_rect(sprite)),
                       cast(get_origin(sprite)),
                       0.0f,
                       WHITE);
    }

    point global_pos(const sprite& sprite)
    {
        return (point{0.0f, 0.0f} * sprite.target) + sprite.position;
    }

    rect global_rect(const sprite& sprite)
    {
        auto dest_rect = get_dest_rect(sprite);
        auto origin = get_origin(sprite);
        dest_rect.x -= origin.x;
        dest_rect.y -= origin.y;
        return dest_rect;
    }

    rect origin_rect(const sprite& sprite)
    {
        auto g_rect = global_rect(sprite);
        auto g_pos = global_pos(sprite);
        g_rect.x -= g_pos.x;
        g_rect.y -= g_pos.y;
        return g_rect;
    }


    bool collision(const dd::sprite& s1, const dd::sprite& s2)
    {
        return collision(s1.bound, global_pos(s1), s2.bound, global_pos(s2));
    }

}
}