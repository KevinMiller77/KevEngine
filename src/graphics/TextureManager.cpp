#include "TextureManager.h"

void TextureManager::AddTexture(const char* ID, GLTextureProgram* Texture)
{
    textures.push_back(Texture);
    textureMap.insert({ ID, textures.size() - 1});
    LOG_INF("New texture in array. Key: %s Value: %d\n", ID, textures.size());
}

void TextureManager::NewTexture(const char* ID, const char* image_path, int tileSize, Vec2f flip)
{
    GLTextureProgram* texture = new GLTextureProgram(image_path, tileSize, flip);
    textures.push_back(texture);
    textureMap.insert({ ID, textures.size() - 1 });
    LOG_INF("New texture in array. Key: %s Value: %d unsigned int %d\n", ID, textures.size() - 1, texture->GetTexID());
}

void TextureManager::ClearTextures()
{
     for (GLTextureProgram* texture : textures)
     {
         delete texture;
     }
     textures.clear(); 
     textureMap.clear();
}

GLTextureProgram* TextureManager::GetTexture(const char* ID)
{
    GLTextureProgram* wantedTex = textures[textureMap[ID]];
    return wantedTex;
}

unsigned int TextureManager::GetNum(const char* ID)
{
    return textureMap[ID];
}
