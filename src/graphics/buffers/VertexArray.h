#ifndef __VERT_ARRAY__
#define __VERT_ARRAY__

#include <vector>

#include <GL/glew.h>
#include "Buffer.h"

class VertexArray
{
private:
    GLuint BufferID;
    std::vector<Buffer*> Buffers;

public:
    VertexArray();
    ~VertexArray();

    void addBuffer(Buffer* buf, GLuint idx);
    void bind() const;
    void unbind() const;
};
#endif