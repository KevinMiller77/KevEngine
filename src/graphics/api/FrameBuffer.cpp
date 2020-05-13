#include "FrameBuffer.h"

#include <core/Core.h>
#include <platform/graphics/GL/buffers/GLFrameBuffer.h>

FrameBuffer* FrameBuffer::Create(int scr_width, int scr_height)
{
#ifdef KEV_RENDERAPI_GL
    return new GLFrameBuffer(scr_width, scr_height);
#endif
}
