#pragma once
#include <vector>
#include <map>
#include <string>

namespace ndn::eng
{

using TextureId = unsigned int;

struct Textures
{
    std::map<std::string, std::vector<TextureId>> textures;
    std::pair<std::string, size_t> selectedTextureIdx = {{}, 0};
    //
    Textures() = default;

    Textures& Add(const TextureId& t);
    Textures& Add(const std::pair<std::string, TextureId>&);
    Textures& Add(const std::vector<TextureId>&);
    Textures& Add(const std::pair<std::string, std::vector<TextureId>>&);
    Textures& Add(const std::map<std::string, std::vector<TextureId>>&);
    Textures& Add(const std::string& fileName, size_t w = 0, size_t h = 0);
    Textures& Add(const std::string& key, const std::string& fileName, size_t w = 0, size_t h = 0);

    TextureId Texture(const std::string& = {}, size_t idx = 0) const;
    const std::vector<TextureId>& TexturesVec(const std::string& = {}) const;

    TextureId Selected() const;
    void Select(size_t idx);
    void Select(const std::string&, size_t idx = 0);
};

}
