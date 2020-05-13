#ifndef __GL_GENERAL_BUFFER__
#define __GL_GENERAL_BUFFER__
#include <graphics/api/Buffer.h>

class GLBuffer : public Buffer {
    unsigned int BufferID;
    unsigned int ComponentCount;

public:
    GLBuffer(float* data, int count, unsigned int compCount);
    ~GLBuffer();

    virtual void Bind() override;
    virtual void Unbind() override;

    virtual unsigned int GetComponentCount() override { return ComponentCount; }
};

#endif
