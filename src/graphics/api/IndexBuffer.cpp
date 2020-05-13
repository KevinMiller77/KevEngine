#include "IndexBuffer.h"
#include <core/Core.h>
#include <platform/graphics/GL/buffers/GLIndexBuffer.h>

IndexBuffer* IndexBuffer::Create(unsigned int *data, int count)
{
#ifdef KEV_RENDERAPI_GL
    return new GLIndexBuffer(data, count);
#endif
}
