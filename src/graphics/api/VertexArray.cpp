#include "VertexArray.h"
#include <core/Core.h>
#include <platform/graphics/GL/buffers/GLVertexArray.h>

using namespace std;

VertexArray* VertexArray::Create()
{
#ifdef KEV_RENDERAPI_GL
    return new GLVertexArray();
#endif
}
