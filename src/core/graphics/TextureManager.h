#ifndef __TEXTURE_MANAGER__
#define __TEXTURE_MANAGER__

#include <string>
#include <vector>
#include <map>

#include "TextureProgram.h"

class TextureManager
{
private:
    std::vector<Texture*> textures;
    std::map<const char*, GLuint, StrCompare> textureMap;

public:
    TextureManager() = default;
    ~TextureManager()
    {
        textures.clear();
        textureMap.clear();
    }

    void AddTexture(const char* ID, Texture* Texture);
    void NewTexture(const char* ID, const char* image_path, Vec2f flip = Vec2f(0.0f, 0.0f));

    void ClearTextures();

    GLuint GetNum(const char* ID);
    Texture* GetTexture(const char* ID);
};

#endif