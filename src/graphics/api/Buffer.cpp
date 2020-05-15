#include "Buffer.h"

#include <core/Core.h>
#include <platform/graphics/GL/buffers/GLBuffer.h>
#include <platform/graphics/Metal/buffers/MetalBuffer.h>

Buffer* Buffer::Create(float *Data, int Count, unsigned int NumComponents)
{
    
#ifdef KEV_RENDERAPI_GL
    return new GLBuffer(Data, NumComponents);
#elif defined KEV_RENDERAPI_METAL
    return new MetalRawBuffer(Data, NumComponents);
#endif
}
