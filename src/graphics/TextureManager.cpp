#include "TextureManager.h"

void TextureManager::addTexture(const char* ID, Texture* Texture)
{
    textures.push_back(Texture);
    textureMap.insert({ ID, textures.size() - 1});
    LOG_INF("New texture in array. Key: %s Value: %d\n", ID, textures.size());
}

void TextureManager::newTexture(const char* ID, const char* image_path, Vec2f flip)
{
    Texture* texture = new Texture(image_path, flip);
    textures.push_back(texture);
    textureMap.insert({ ID, textures.size() - 1 });
    LOG_INF("New texture in array. Key: %s Value: %d GLuint %d\n", ID, textures.size() - 1, texture->getTextureID());
}

void TextureManager::clearTextures()
{
     for (Texture* texture : textures)
     {
         delete texture;
     }
     textures.clear(); 
     textureMap.clear();
}

Texture* TextureManager::getTexture(const char* ID)
{
    Texture* wantedTex = textures[textureMap[ID]];
    return wantedTex;
}

GLuint TextureManager::getNum(const char* ID)
{
    return textureMap[ID];
}