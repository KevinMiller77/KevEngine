#ifndef __GL_GENERAL_BUFFER__
#define __GL_GENERAL_BUFFER__
#include <graphics/api/Buffer.h>

class GLBuffer : public Buffer {
    unsigned int m_BufferID;
    unsigned int m_ComponentCount;

public:
    GLBuffer(float* Data, int NumComponents);
    ~GLBuffer();

    virtual void Bind() override;
    virtual void Unbind() override;
    inline virtual void* GetBuffer() override { return (void*)&m_BufferID; }

    virtual unsigned int GetComponentCount() override { return m_ComponentCount; }
};

#endif
