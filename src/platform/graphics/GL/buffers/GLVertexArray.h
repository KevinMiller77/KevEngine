#ifndef __GL_VERT_ARRAY__
#define __GL_VERT_ARRAY__
#include <vector>
#include "GLBuffer.h"

#include <graphics/api/VertexArray.h>

class GLVertexArray : public VertexArray
{
private:
    unsigned int BufferID;
    std::vector<GLBuffer*> Buffers;

public:
    GLVertexArray();
    ~GLVertexArray();

    virtual void AddBuffer(Buffer* buf, unsigned int idx) override;
    virtual void Bind() const override;
    virtual void Unbind() const override;
};
#endif
