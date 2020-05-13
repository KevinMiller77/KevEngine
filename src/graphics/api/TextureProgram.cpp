#include "TextureProgram.h"

#include <core/Core.h>
#include <platform/graphics/GL/renderer/GLTextureProgram.h>

TextureProgram* TextureProgram::Create(const char *inImagePath, unsigned int TileSize, Vec2f flip)
{
#ifdef KEV_RENDERAPI_GL
    return new GLTextureProgram(inImagePath, TileSize, flip);
#endif
}
