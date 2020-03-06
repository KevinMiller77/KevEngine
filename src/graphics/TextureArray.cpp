#include "TextureArray.h"

void TextureArray::addTexture(const char* ID, Texture* Texture)
{
    textures.push_back(Texture);
    textureMap.insert({ ID, textures.size() - 1});
    LOG_INF("New texture in array. Key: %s Value: %d\n", ID, textures.size());
}

void TextureArray::newTexture(const char* ID, const char* image_path, Vec2f flip)
{
    Texture* texture = new Texture(image_path, flip);
    textures.push_back(texture);
    textureMap.insert({ ID, textures.size() - 1 });
    LOG_INF("New texture in array. Key: %s Value: %d\n", ID, textures.size());
}

void TextureArray::clearTextures()
{
     for (Texture* texture : textures)
     {
         delete texture;
     }
     textures.clear(); 
     textureMap.clear();
}

Texture* TextureArray::getTexture(const char* ID)
{
    Texture* wantedTex = textures[textureMap[ID]];
    return wantedTex;
}

GLuint TextureArray::getNum(const char* ID)
{
    return textureMap[ID];
}