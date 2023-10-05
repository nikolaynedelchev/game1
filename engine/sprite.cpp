#include "sprite.h"

void test_loader()
{
    std::cout << "Hello from loader" << std::endl;
}

void Sprite_Load(Sprite& sprite, string imageFile )
{
    Sprite_Load(sprite, {0.0f, 0.0f, 0.0f, 0.0f}, imageFile);
}

void Sprite_Load(Sprite &sprite, Rectangle sourceSubimage, string imageKey)
{
    sprite.isLoaded = false;

    Image image = GetImage(imageKey);
    if (image.data == nullptr)
    {
        PrintLn("Error: Empty image: {}", imageKey);
        return;
    }
    sprite.texture = LoadTextureFromImage(image);
    if (sprite.texture.id == 0)
    {
        PrintLn("Error: Texture construct failed: {}", imageKey);
        return;
    }
    sprite.rotate = 0.0f;
    if (sourceSubimage.x != 0.0f || sourceSubimage.y != 0.0 ||
        sourceSubimage.width != 0.0f || sourceSubimage.height != 0.0)
    {
        sprite.sourceSubimage = sourceSubimage;
    }
    else
    {
        sprite.sourceSubimage = {0.0f, 0.0f, float(sprite.texture.width), float(sprite.texture.height)};
    }
    sprite.position = {0.0f, 0.0f, float(sprite.texture.width), float(sprite.texture.height)};
    sprite.enabled = true;
    sprite.isLoaded = true;
}

void Sprite_Unload(Sprite&sprite)
{
    UnloadTexture(sprite.texture);
}

void Sprite_Draw(const Sprite& sprite)
{
    if (sprite.isLoaded == false ||
        sprite.enabled == false)
    {
        return;
    }
    DrawTexturePro(sprite.texture, 
                   sprite.sourceSubimage, 
                   {
                        // destination rectangle
                        sprite.position.x - float(sprite.sourceSubimage.width) / 2.0f,
                        sprite.position.y - float(sprite.sourceSubimage.height) / 2.0f,
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