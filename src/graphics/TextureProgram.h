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
    GLuint width;
    GLuint height;
    GLint nrChannels;

    GLuint texture;

public:
    Texture(const char *inImagePath);
    void bind();
    void unbind();
};

#endif