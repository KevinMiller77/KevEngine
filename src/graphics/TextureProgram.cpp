#include "TextureProgram.h"

Texture::Texture() 
{
    texture = 0;
    imagePath = nullptr;
    width = 0;
    height = 0;
}

Texture::Texture(const char *inImagePath)
    : imagePath(inImagePath)
{
    init();
}

void Texture::init()
{
    FreeImage_Initialise();

    BYTE* image = ImageLoad(imagePath, &width, &height);
    
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (image)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, image);
        LOG_INF("Texture (%s) loaded\n", imagePath);
    }
    else
    {
        LOG_WRN("Failed to load texture (%s)\n", imagePath);
    }

    FreeImage_DeInitialise();
    glBindTexture(GL_TEXTURE_2D, 0);
}

BYTE* Texture::ImageLoad(const char* path, GLuint *width, GLuint *height)
{
    FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	FIBITMAP *dib = nullptr;
	fif = FreeImage_GetFileType(path, 0);
	if (fif == FIF_UNKNOWN)
		fif = FreeImage_GetFIFFromFilename(path);
	if (fif == FIF_UNKNOWN)
		return nullptr;

	if (FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, path);
	if (!dib)
		return nullptr;

	BYTE* result = FreeImage_GetBits(dib);
	*width = FreeImage_GetWidth(dib);
	*height = FreeImage_GetHeight(dib);

	return result;
}

void Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, texture);
}

void Texture::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}