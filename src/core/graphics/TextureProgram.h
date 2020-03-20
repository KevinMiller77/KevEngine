#ifndef __TEXTURE_PROGRAM__
#define __TEXTURE_PROGRAM__

#define FREEIMAGE_LIB
#include <stb_image/stb_image.h>

#include "../utils/Logging.h"
#include "../utils/FileIO.h"
#include "../math/math.h"

class Texture
{
private:
    char *imagePath;
    int width, height;
    int nrChannels;

    unsigned int texture;
    void* heapLocOfTexture;

public:
    Texture();
    Texture(const char *inImagePath, Vec2f flip = Vec2f(0.0f, 0.0f));
    ~Texture();
    void Init(Vec2f flip = Vec2f(0.0f, 0.0f));
    void Bind();
    void Unbind();

    inline const unsigned int GetTexID() const { return texture; }
};

#endif