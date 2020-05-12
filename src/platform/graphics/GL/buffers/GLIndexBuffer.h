#ifndef __INDEX_BUFFER__
#define __INDEX_BUFFER__
#include <cstdlib>
// #include <GLFW/glfw3.h>

class GLIndexBuffer
{
private:
    unsigned int BufferID;
    unsigned int Count;
    unsigned int* HeapLoc;

public:
    GLIndexBuffer(unsigned int *data, int count);
    ~GLIndexBuffer();

    void Bind() const;
    void Unbind() const;

    inline unsigned int GetCount() const { return Count; }
};

#endif
