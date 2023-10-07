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
    uint32_t textureId = s_textures.size();
    string fullFileName = "../resources/images/" + imageFile;
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
        sprite.textureId = id_it->second;
        texture texture = s_textures[sprite.textureId];
        sprite.rotate = 0.0f;
        sprite.source = source;
        if (sprite.source.width == 0.0f && sprite.source.height == 0.0f)
        {
            sprite.source.width = float(texture.width);
            sprite.source.height = float(texture.height);
        }
        sprite.target = targetTransform;
        sprite.position = {0.0f, 0.0f};
        sprite.enabled = true;
        sprite.isLoaded = true;
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
        if (sprite.isLoaded == false ||
            sprite.enabled == false)
        {
            return;
        }

        DrawTexturePro(cast(s_textures[ sprite.textureId ]), 
                       cast(sprite.source),
                       cast(get_dest_rect(sprite)),
                       cast(get_origin(sprite)),
                       0.0f,
                       WHITE);

        draw(global_rect(sprite), colors::white);
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

}
}