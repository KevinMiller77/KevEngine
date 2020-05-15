#ifndef __METAL_TEXTURE_PROGRAM__
#define __METAL_TEXTURE_PROGRAM__

#define FREEIMAGE_LIB
#include <stb_image/stb_image.h>

#include <utils/Logging.h>
#include <utils/FileIO.h>
#include <math/math.h>
#include <graphics/api/TextureProgram.h>

class MetalTextureProgram : public TextureProgram
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
    MetalTextureProgram(const char *inImagePath, unsigned int TileSize, Vec2f flip);
    ~MetalTextureProgram();
    void Init(Vec2f flip = Vec2f(0.0f, 0.0f)) override;
    void Bind() override;
    void Unbind() override;

    inline const unsigned int GetTexID() override { return texture; }
    inline const bool IsTilesheet() override  { return tileSheet; }
    inline const int GetTileSize() override  { return tileSize; }
    inline const int GetWidth() override  { return width; }
    inline const int GetHeight() override  { return height; }
    inline const Vec2u GetSize() override  { return Vec2u(width, height); }
};

#endif
