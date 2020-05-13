#ifndef __VERT_ARRAY__
#define __VERT_ARRAY__

#include <vector>
#include "Buffer.h"

class VertexArray
{
public:
    virtual void AddBuffer(Buffer* buf, unsigned int idx) = 0;
    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    static VertexArray* Create();
};
#endif
