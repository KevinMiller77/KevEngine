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
        for (Texture* tex : textures)
        {
            delete tex;
        }
    }

    void addTexture(const char* ID, Texture* Texture);
    void newTexture(const char* ID, const char* image_path, Vec2f flip = Vec2f(0.0f, 0.0f));

    void clearTextures();

    GLuint getNum(const char* ID);
    Texture* getTexture(const char* ID);

    void _delete() {
        for (Texture* texture : textures)
            delete texture;
        textureMap = std::map<const char*, GLuint, StrCompare>();
    }
};

#endif