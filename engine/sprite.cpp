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
    s_texturesIds[imageFile] = s_textures.size();
    s_textures.push_back(texture);
    UnloadImage(image);
    return true;
}

Sprite CreateSprite(const string& imageFile, 
                    Rectangle sourceShape, 
                    float scale, 
                    Vector2 offset)
{
    auto textureIdIt = s_texturesIds.find(imageFile);
    if (textureIdIt == s_texturesIds.end())
    {
        if (CreateTexture(imageFile) == false)
        {
            FatalError("Faild to create texture: {}", imageFile);
            return Sprite();
        }
        textureIdIt = s_texturesIds.find(imageFile);
        if (textureIdIt == s_texturesIds.end())
        {
            FatalError("Error: CreateTexture unknown failier: {}", imageFile);
            return Sprite();
        }
    }
    Sprite sprite;
    sprite.textureId = textureIdIt->second;
    Texture2D texture = s_textures[sprite.textureId];
    sprite.rotate = 0.0f;
    if (sourceShape.x != 0.0f || sourceShape.y != 0.0f ||
        sourceShape.width != 0.0f || sourceShape.height != 0.0f)
    {
        sprite.sourceShape = sourceShape;
    }
    else
    {
        sprite.sourceShape = {0.0f, 0.0f, float(texture.width), float(texture.height)};
    }
    sprite.targetShape = {0.0f, 0.0f, float(texture.width), float(texture.height)};
    sprite.position = {0.0f, 0.0f};
    sprite.enabled = true;
    sprite.isLoaded = true;
    sprite.targetShape *= scale;
    sprite.targetShape += offset * scale;
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
                   sprite.sourceShape,
                   sprite.targetShape + sprite.position,
                   {
                        // origin of the sprite (set to the center of the image)
                        float(sprite.targetShape.width) / 2.0f,
                        float(sprite.targetShape.height) / 2.0f
                   }, 
                   sprite.rotate, WHITE);

}