#ifndef __GL_INDEX_BUFFER__
#define __GL_INDEX_BUFFER__
#include <cstdlib>

#include <graphics/api/IndexBuffer.h>

class GLIndexBuffer : public IndexBuffer
{
private:
    unsigned int m_BufferID;
    unsigned int m_Count;
    unsigned int* m_HeapLoc;

public:
    GLIndexBuffer(unsigned int *data, int count);
    ~GLIndexBuffer();

    virtual void Bind() const override;
    virtual void Unbind() const override;
    
    inline virtual void* GetBuffer() override { return (void*)&m_BufferID; }

    inline unsigned int GetCount() const override { return m_Count; }
};

#endif
