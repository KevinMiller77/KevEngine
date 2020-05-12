#ifndef __TEXTURE_PROGRAM__
#define __TEXTURE_PROGRAM__

#define FREEIMAGE_LIB
#include <stb_image/stb_image.h>

#include <utils/Logging.h>
#include <utils/FileIO.h>
#include <math/math.h>

class GLTextureProgram
{
private:
    char *imagePath;
    int width, height;
    int tileSize;
    int nrChannels;

    bool tileSheet;

    unsigned int texture;
    void* heapLocOfTexture;

public:
    GLTextureProgram();
    GLTextureProgram(const char *inImagePath, unsigned int TileSize = 0, Vec2f flip = Vec2f(0.0f, 0.0f));
    ~GLTextureProgram();
    void Init(Vec2f flip = Vec2f(0.0f, 0.0f));
    void Bind();
    void Unbind();

    inline const unsigned int GetTexID() const { return texture; }
    inline const bool IsTilesheet() { return tileSheet; }
    inline const int GetTileSize() { return tileSize; }
    inline const int GetWidth() { return width; }
    inline const int GetHeight() { return height; }
    inline const Vec2u GetSize() { return Vec2u(width, height); }
};

#endif
