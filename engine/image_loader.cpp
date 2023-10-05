#include "image_loader.h"

map<string, Image> allLoadedImages;
void LoadImage(string imageFile, string imageKey)
{
    if (allLoadedImages.find(imageKey) != allLoadedImages.end())
    {
        UnloadImage(allLoadedImages[imageKey]);
    }
    allLoadedImages[imageKey] = LoadImage(imageFile.c_str());
}

Image GetImage(string imageKey)
{
    auto it = allLoadedImages.find(imageKey);
    if (it == allLoadedImages.end())
    {
        Image empty;
        empty.data = nullptr;
        empty.height = 0;
        empty.width = 0;
        return empty;
    }
    return it->second;
}

void UnloadAllImages()
{
    for(auto& p : allLoadedImages)
    {
        if (p.second.data)
        {
            UnloadImage(p.second);
            p.second.data = nullptr;
        }
    }
    allLoadedImages.clear();
}
