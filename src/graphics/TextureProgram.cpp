#include "TextureProgram.h"

Texture::Texture(const char *inImagePath)
    : imagePath(inImagePath)
{
    FreeImage_Initialise();

    LOG_INF("Extracting texture information from: %s\n", imagePath);
    FIBITMAP *bitmap = FreeImage_Load(
        FreeImage_GetFileType(imagePath),
        imagePath);
    FIBITMAP *image = FreeImage_ConvertTo32Bits(bitmap);

    width = FreeImage_GetWidth(image);
    height = FreeImage_GetHeight(image);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (image)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void *)FreeImage_GetBits(image));

        FreeImage_Unload(image);
    }
    else
    {
        LOG_WRN("Failed to load texture.");
    }

    FreeImage_DeInitialise();
    glBindTexture(GL_TEXTURE_2D, 0);
    LOG_INF("Texture loaded\n");
}

void Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, texture);
}

void Texture::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}