#include "TextureProgram.h"

#include <assert.h>
#include <glad/glad.h>

Texture::Texture() 
{
    texture = 0;
    nrChannels = 0;
    width = 0;
    height = 0;
    imagePath = nullptr;
    heapLocOfTexture = nullptr;
}

Texture::Texture(const char *inImagePath, unsigned int TileSize, Vec2f flip)
{
    tileSheet = (bool)TileSize;
    tileSize = TileSize;
    imagePath = (char*) inImagePath;
    Init(flip);
}

Texture::~Texture()
{
    glDeleteTextures(1, &texture);
    delete heapLocOfTexture;
}

void Texture::Init(Vec2f flip)
{
    stbi_set_flip_vertically_on_load(1);

    stbi_uc* image = nullptr;
    image = stbi_load(imagePath, &width, &height, &nrChannels, 4);
    
    unsigned int InternalFormat = GL_RGBA8;
    unsigned int DataFormat = GL_RGBA;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (image)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, InternalFormat, width, height, 0, DataFormat, GL_UNSIGNED_BYTE, image);
        
        LOG_INF("Texture (%s) loaded\n", imagePath);
    }
    else
    {
        LOG_WRN("Failed to load texture (%s)\n", imagePath);
        LOG_INF("Reason for fail: %s\n", stbi_failure_reason());
    }

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(image);

}
void Texture::Bind()
{
    glBindTexture(GL_TEXTURE_2D, texture);
}

void Texture::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}