#ifndef __TEXTURE_PROGRAM__
#define __TEXTURE_PROGRAM__

#include <math/math.h>

class TextureProgram
{
public:
    virtual void Init(Vec2f flip = Vec2f(0.0f, 0.0f)) = 0;
    virtual void Bind() = 0;
    virtual void Unbind() = 0;

    virtual const unsigned int GetTexID() = 0;
    virtual const bool IsTilesheet() = 0;
    virtual const int GetTileSize() = 0;
    virtual const int GetWidth() = 0;
    virtual const int GetHeight() = 0;
    virtual const Vec2u GetSize() = 0;
    
    static TextureProgram* Create(const char *inImagePath, unsigned int TileSize = 0, Vec2f flip = Vec2f(0.0f, 0.0f));
};

#endif
