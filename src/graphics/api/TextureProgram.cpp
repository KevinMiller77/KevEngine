#include "TextureProgram.h"

#include <core/Core.h>
#include <platform/graphics/GL/renderer/GLTextureProgram.h>
#include <platform/graphics/Metal/renderer/MetalTextureProgram.h>

TextureProgram* TextureProgram::Create(const char *inImagePath, unsigned int TileSize, Vec2f flip)
{
#ifdef KEV_RENDERAPI_GL
    return new GLTextureProgram(inImagePath, TileSize, flip);
#elif defined KEV_RENDERAPI_METAL
    return new MetalTextureProgram(inImagePath, TileSize, flip);
#endif
}
