#ifndef __VERT_ARRAY__
#define __VERT_ARRAY__

#include <vector>
#include "GLBuffer.h"

class GLVertexArray
{
private:
    unsigned int BufferID;
    std::vector<GLBuffer*> Buffers;

public:
    GLVertexArray();
    ~GLVertexArray();

    void AddBuffer(GLBuffer* buf, unsigned int idx);
    void Bind() const;
    void Unbind() const;
};
#endif
