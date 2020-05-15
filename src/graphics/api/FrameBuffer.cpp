#include "FrameBuffer.h"

#include <core/Core.h>
#include <platform/graphics/GL/buffers/GLFrameBuffer.h>
#include <platform/graphics/Metal/buffers/MetalFrameBuffer.h>

FrameBuffer* FrameBuffer::Create(int scr_width, int scr_height)
{
#ifdef KEV_RENDERAPI_GL
    return new GLFrameBuffer(scr_width, scr_height);
#elif defined KEV_RENDERAPI_METAL
    return new MetalFrameBuffer(scr_width, scr_height);
#endif
}
