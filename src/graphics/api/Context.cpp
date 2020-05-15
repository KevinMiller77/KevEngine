
#include <core/Core.h>

#include <assert.h>
#include "Context.h"

#include <platform/graphics/GL/renderer/GLContext.h>
#include <platform/graphics/Metal/renderer/MetalContext.h>

Context* Context::Create(GLFWwindow* windowHandle)
{
#ifdef KEV_RENDERAPI_GL
    return new GLContext(windowHandle);
#elif defined KEV_RENDERAPI_METAL
    return new MetalContextLayer(windowHandle);
#endif
}
