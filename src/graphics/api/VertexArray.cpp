#include "VertexArray.h"

#include <core/Core.h>
#include <platform/graphics/GL/buffers/GLVertexArray.h>
#include <platform/graphics/Metal/buffers/MetalVertexArray.h>

using namespace std;

VertexArray* VertexArray::Create()
{
#ifdef KEV_RENDERAPI_GL
    return new GLVertexArray();
#elif defined KEV_RENDERAPI_METAL
    return new MetalVertexArray();
#endif
}
