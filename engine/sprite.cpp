#include "sprite.h"

static map<string, uint32_t> s_texturesIds;
static vector<Texture2D> s_textures;

static bool CreateTexture(const string& imageFile)
{
    if (s_texturesIds.find(imageFile) != s_texturesIds.end())
    {
        return true;
    }
    uint32_t textureId = s_textures.size();
    Image image = LoadImage(imageFile.c_str());
    if (image.data == nullptr)
    {
        PrintLn("Error: Empty image: {}", imageFile);
        return false;
    }
    Texture2D texture = LoadTextureFromImage(image);
    if (texture.id == 0)
    {
        UnloadImage(image);
        PrintLn("Error: Texture construct failed: {}", imageFile);
        return false;
    }
    s_texturesIds[imageFile] = s_textures.size();
    s_textures.push_back(texture);
    UnloadImage(image);
    return true;
}

Sprite CreateSprite(const string& imageFile, Rectangle sourceSubimage)
{
    if (CreateTexture(imageFile) == false)
    {
        return Sprite();
    }
    Sprite sprite;
    sprite.textureId = s_texturesIds[imageFile];
    Texture2D texture = s_textures[sprite.textureId];
    sprite.rotate = 0.0f;
    if (sourceSubimage.x != 0.0f || sourceSubimage.y != 0.0f ||
        sourceSubimage.width != 0.0f || sourceSubimage.height != 0.0f)
    {
        sprite.sourceSubimage = sourceSubimage;
    }
    else
    {
        sprite.sourceSubimage = {0.0f, 0.0f, float(texture.width), float(texture.height)};
    }
    sprite.position = {0.0f, 0.0f, float(texture.width), float(texture.height)};
    sprite.enabled = true;
    sprite.isLoaded = true;
    return sprite;
}

void ReleaseSpritres()
{
    for(auto& t : s_textures)
    {
        UnloadTexture(t);   
    }
    s_textures.clear();
    s_texturesIds.clear();
}

void DrawSprite(const Sprite& sprite)
{
    if (sprite.isLoaded == false ||
        sprite.enabled == false)
    {
        return;
    }
    DrawTexturePro(s_textures[ sprite.textureId ], 
                   sprite.sourceSubimage, 
                   {
                        // destination rectangle
                        sprite.position.x,
                        sprite.position.y,
                        float(sprite.sourceSubimage.width),
                        float(sprite.sourceSubimage.height)
                   },
                   {
                        // origin of the sprite (set to the center of the image)
                        float(sprite.sourceSubimage.width) / 2.0f,
                        float(sprite.sourceSubimage.height) / 2.0f
                   }, 
                   sprite.rotate, WHITE);

}