#ifndef __FRAME_BUFFER__
#define __FRAME_BUFFER__

#include <utils/Logging.h>

class FrameBuffer
{
private:
    unsigned int FBO;
    int m_W, m_H;
    unsigned int texture;

public:
    FrameBuffer(int scr_width, int scr_height);

    void Bind(int scr_width, int scr_height);
    void Unbind();

    inline unsigned int GetTexture() { return texture; }

};

#endif