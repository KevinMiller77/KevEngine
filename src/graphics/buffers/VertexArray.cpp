#ifndef __VERTEX_ARRAY__
#define __VERTEX_ARRAY__
#include "VertexArray.h"

using namespace std;

VertexArray::VertexArray()
:
Buffers()
{
    glGenVertexArrays(1, &BufferID);
}

VertexArray::~VertexArray()
{
    for (uint32_t i = 0; i < Buffers.size(); i++)
    {
        delete Buffers[i];
    }
}

void VertexArray::addBuffer(Buffer* buf, GLuint idx)
{
    bind();
    buf->bind();

    glEnableVertexAttribArray(idx);
    glVertexAttribPointer(idx, buf->getComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);

    buf->unbind();
    unbind();
}

void VertexArray::bind() const
{
    glBindVertexArray(BufferID);
}

void VertexArray::unbind() const
{
    glBindVertexArray(BufferID);
}

#endif