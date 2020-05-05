#ifndef __TEXTURE_MANAGER__
#define __TEXTURE_MANAGER__

#include <string>
#include <vector>
#include <map>

#include <graphics/renderer/TextureProgram.h>

class TextureManager
{
private:
    std::vector<Texture*> textures;
    std::map<const char*, unsigned int, StrCompare> textureMap;

public:
    TextureManager() = default;
    ~TextureManager()
    {
        textures.clear();
        textureMap.clear();
    }

    void AddTexture(const char* ID, Texture* Texture);
    void NewTexture(const char* ID, const char* image_path, int tileSize = 0, Vec2f flip = Vec2f(0.0f, 0.0f));

    void ClearTextures();

    unsigned int GetNum(const char* ID);
    Texture* GetTexture(const char* ID);
};

#endif