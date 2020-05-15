#include "IndexBuffer.h"
#include <core/Core.h>
#include <platform/graphics/GL/buffers/GLIndexBuffer.h>
#include <platform/graphics/Metal/buffers/MetalIndexBuffer.h>

IndexBuffer* IndexBuffer::Create(unsigned int *data, int count)
{
#ifdef KEV_RENDERAPI_GL
    return new GLIndexBuffer(data, count);
#elif defined KEV_RENDERAPI_METAL
    return new MetalIndexBuffer(data, count);
#endif
}
