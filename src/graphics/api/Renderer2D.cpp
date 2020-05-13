#include "GLRenderer2D.h"

#include <core/Core.h>
#include <platform/graphics/GL/renderer/GLRenderer2D.h>

Renderer2D* Renderer2D::Create(int* width, int* height)
{
#ifdef KEV_RENDERAPI_GL
    return new GLRenderer2D(width, height);
#endif
}
