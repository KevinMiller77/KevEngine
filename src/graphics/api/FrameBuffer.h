
#ifndef __FRAME_BUFFER__
#define __FRAME_BUFFER__

#include <utils/Logging.h>

class FrameBuffer
{
public:
    virtual void Bind(int scr_width, int scr_height) = 0;
    virtual void Unbind() = 0;

    virtual unsigned int GetTexture() = 0;

    static FrameBuffer* Create(int scr_width, int scr_height);
};

#endif
