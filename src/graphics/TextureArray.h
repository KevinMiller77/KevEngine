#ifndef __TEXTURE_ARRAY__
#define __TEXTURE_ARRAY__

#include <string>
#include <vector>
#include <map>

#include "TextureProgram.h"

class TextureArray
{
private:
    std::vector<Texture*> textures;
    std::map<const char*, GLuint, StrCompare> textureMap;

public:
    TextureArray() = default;
    ~TextureArray()
    {
        textures.clear();
        textureMap.clear();
    }

    void addTexture(const char* ID, Texture* Texture);
    void newTexture(const char* ID, const char* image_path, Vec2f flip = Vec2f(0.0f, 0.0f));

    void clearTextures();

    GLuint getNum(const char* ID);
    Texture* getTexture(const char* ID);
};

#endif