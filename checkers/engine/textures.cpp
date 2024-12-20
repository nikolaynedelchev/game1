#include "textures.h"

namespace ndn::eng
{

Textures& Textures::Add(const TextureId& t)
{
    textures[{}].push_back(t);
    return *this;
}

Textures& Textures::Add(const std::pair<std::string, TextureId>& p)
{
    textures[p.first].push_back(p.second);
    return *this;
}

Textures& Textures::Add(const std::vector<TextureId>& v)
{
    return Add({std::string(), v});
}

Textures& Textures::Add(const std::pair<std::string, std::vector<TextureId>>& p)
{
    for(auto t : p.second)textures[p.first].push_back(t);
    return *this;
}

Textures& Textures::Add(const std::map<std::string, std::vector<TextureId>>& m)
{
    for(const auto& p : m)
    {
        Add(p);
    }
    return *this;
}

Textures &Textures::Add(const std::string &fileName, size_t w, size_t h)
{

}

TextureId Textures::Texture(const std::string & key, size_t idx) const
{
    auto it = textures.find(key);
    if (it == textures.end() || it->second.size() <= idx) return 0;
    return it->second[idx];
}

const std::vector<TextureId> &Textures::TexturesVec(const std::string & key) const
{
    static std::vector<TextureId> s_empty;
    auto it = textures.find(key);
    if (it == textures.end()) return s_empty;
    return it->second;
}

TextureId Textures::Selected() const
{
    return Texture(selectedTextureIdx.first, selectedTextureIdx.second);
}

void Textures::Select(size_t idx)
{
    Select({}, idx);
}

void Textures::Select(const std::string& key, size_t idx)
{
    selectedTextureIdx = {key, idx};
}

}
