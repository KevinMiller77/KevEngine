#ifndef __TEXTURE_PROGRAM__
#define __TEXTURE_PROGRAM__

#define FREEIMAGE_LIB
#include <FreeImage/FreeImage.h>

#include "GL/glew.h"

#include "../utils/Logging.h"
#include "../utils/FileIO.h"

#include "../math/math.h"

class Texture
{
private:
    char *imagePath;
    GLuint width, height;
    GLint nrChannels;

    GLuint texture;
    FIBITMAP* heapLocOfTexture;

public:
    Texture();
    Texture(const char *inImagePath, Vec2f flip = Vec2f(0.0f, 0.0f));
    ~Texture();
    void Init(Vec2f flip = Vec2f(0.0f, 0.0f));
    BYTE* ImageLoad(const char* path, GLuint *width, GLuint *height, FREE_IMAGE_FORMAT* format, Vec2f flip = Vec2f(0.0f, 0.0f));
    void Bind();
    void Unbind();

    inline const GLuint GetTexID() const { return texture; }
};

#endif