#include "TextureProgram.h"



Texture::Texture() 
{
    texture = 0;
    nrChannels = 0;
    width = 0;
    height = 0;
    imagePath = nullptr;
    heapLocOfTexture = nullptr;
}

Texture::Texture(const char *inImagePath, Vec2f flip)
{
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
    FreeImage_Initialise();

    FREE_IMAGE_FORMAT formatOfImage;
    BYTE* image = ImageLoad(imagePath, &width, &height, &formatOfImage, flip);
    
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (image)
    {
        if (formatOfImage == FIF_PNG)
        {
            LOG_INF("PNG loaded\n");
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, image);
        }
        else
        {
            LOG_INF("Loading texture of %d type\n", (int)formatOfImage);
           glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, image);
        }
        
        LOG_INF("Texture (%s) loaded\n", imagePath);
    }
    else
    {
        LOG_WRN("Failed to load texture (%s)\n", imagePath);
    }

    FreeImage_DeInitialise();
    glBindTexture(GL_TEXTURE_2D, 0);

}

BYTE* Texture::ImageLoad(const char* path, GLuint *width, GLuint *height, FREE_IMAGE_FORMAT* format, Vec2f flip)
{
    FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	FIBITMAP *dib = nullptr;
	fif = FreeImage_GetFileType(path, 0);
    *format = fif;

    //Get file info
	if (fif == FIF_UNKNOWN)
    {
        fif = FreeImage_GetFIFFromFilename(path);
    }
	if (fif == FIF_UNKNOWN)
    {
		return nullptr;
    }

    //Read file
	if (FreeImage_FIFSupportsReading(fif))
    {
		dib = FreeImage_Load(fif, path);
    }
	if (!dib)
    {
	    return nullptr;
    }

    if((bool)(int)flip.x && dib)
    {
        LOG_INF("Flipping texture H\n");
        FreeImage_FlipHorizontal(dib);
    }
    if((bool)(int)flip.y && dib)
    {
        LOG_INF("Flipping texture V\n");
        FreeImage_FlipHorizontal(dib);
    }


	BYTE* result = FreeImage_GetBits(dib);
	*width = FreeImage_GetWidth(dib);
	*height = FreeImage_GetHeight(dib);
    heapLocOfTexture = dib;

	return result;
}

void Texture::Bind()
{
    glBindTexture(GL_TEXTURE_2D, texture);
}

void Texture::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}