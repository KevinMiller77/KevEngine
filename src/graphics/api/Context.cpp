
#include <core/Core.h>

#include <assert.h>
#include "Context.h"
#include <platform/graphics/GL/renderer/GLContext.h>

Context* Context::Create(GLFWwindow* windowHandle)
{
#ifdef KEV_RENDERAPI_GL
    return new GLContext(windowHandle);
#endif
}
