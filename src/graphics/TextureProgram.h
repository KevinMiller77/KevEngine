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
    const char *imagePath;
    GLuint width, height;
    GLint nrChannels;

    GLuint texture;
    BYTE* heapLoc;

public:
    Texture();
    Texture(const char *inImagePath, Vec2f flip = Vec2f(0.0f, 0.0f));
    ~Texture();
    void init(Vec2f flip = Vec2f(0.0f, 0.0f));
    BYTE* ImageLoad(const char* path, GLuint *width, GLuint *height, Vec2f flip = Vec2f(0.0f, 0.0f));
    void bind();
    void unbind();

    inline const GLuint getTextureID() const { return texture; }
};

#endif