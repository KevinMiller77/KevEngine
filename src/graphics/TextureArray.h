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
    std::map<const char*, GLuint> textureMap;

public:
    TextureArray() = default;

    void addTexture(const char* ID, Texture* Texture);
    void newTexture(const char* ID, const char* image_path);

    GLuint getNum(const char* ID);
    Texture* getTexture(const char* ID);
};

#endif