#ifndef __GL_FRAME_BUFFER__
#define __GL_FRAME_BUFFER__

#include <utils/Logging.h>

#include <graphics/api/FrameBuffer.h>

class GLFrameBuffer : public FrameBuffer
{
private:
    unsigned int FBO;
    int m_W, m_H;
    unsigned int texture;

public:
    GLFrameBuffer(int scr_width, int scr_height);

    virtual void Bind(int scr_width, int scr_height) override;
    virtual void Unbind() override;

    virtual inline unsigned int GetTexture() override { return texture; }

};

#endif
