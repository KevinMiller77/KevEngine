#ifndef __GL_INDEX_BUFFER__
#define __GL_INDEX_BUFFER__
#include <cstdlib>

#include <graphics/api/IndexBuffer.h>

class GLIndexBuffer : public IndexBuffer
{
private:
    unsigned int BufferID;
    unsigned int Count;
    unsigned int* HeapLoc;

public:
    GLIndexBuffer(unsigned int *data, int count);
    ~GLIndexBuffer();

    virtual void Bind() const override;
    virtual void Unbind() const override;

    inline unsigned int GetCount() const override { return Count; }
};

#endif
