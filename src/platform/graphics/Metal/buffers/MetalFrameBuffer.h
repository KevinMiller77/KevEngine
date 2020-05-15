#ifndef __METAL_FRAME_BUFFER__
#define __METAL_FRAME_BUFFER__

#include <utils/Logging.h>
#include <graphics/api/FrameBuffer.h>
#include <platform/graphics/Metal/Metal.h>

class MetalFrameBuffer : public FrameBuffer
{
private:
    id<MTLBuffer> FBO;
    int m_W, m_H;
    unsigned int texture;

public:
    MetalFrameBuffer(int scr_width, int scr_height);

    virtual void Bind(int scr_width, int scr_height) override;
    virtual void Unbind() override;

    virtual unsigned int GetTexture() override { return texture; }

};

#endif
