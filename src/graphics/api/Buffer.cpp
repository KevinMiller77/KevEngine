#include "Buffer.h"

#include <core/Core.h>
#include <platform/graphics/GL/buffers/GLBuffer.h>

Buffer* Buffer::Create(float *data, int count, unsigned int compCount)
{
#ifdef KEV_RENDERAPI_GL
    return new GLBuffer(data, count, compCount);
#endif
}