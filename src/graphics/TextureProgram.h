#ifndef __TEXTURE_PROGRAM__
#define __TEXTURE_PROGRAM__

#define FREEIMAGE_LIB
#include <FreeImage/FreeImage.h>

#include <GL/glew.h>
#include <math.h>

#include "../utils/Logging.h"

class Texture
{
private:
    const char *imagePath;
    GLuint width, height;
    GLint nrChannels;

    GLuint texture;

public:
    Texture();
    Texture(const char *inImagePath);
    void init();
    BYTE* ImageLoad(const char* path, GLuint *width, GLuint *height);
    void bind();
    void unbind();

    inline const GLuint getTextureID() const { return texture; }
};

#endif