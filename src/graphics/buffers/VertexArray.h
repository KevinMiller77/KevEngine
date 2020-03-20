#ifndef __VERT_ARRAY__
#define __VERT_ARRAY__

#include <vector>
#include "Buffer.h"

class VertexArray
{
private:
    unsigned int BufferID;
    std::vector<Buffer*> Buffers;

public:
    VertexArray();
    ~VertexArray();

    void AddBuffer(Buffer* buf, unsigned int idx);
    void Bind() const;
    void Unbind() const;
};
#endif