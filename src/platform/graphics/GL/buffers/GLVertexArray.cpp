#ifndef __VERTEX_ARRAY__
#define __VERTEX_ARRAY__
#include "GLVertexArray.h"
#include <utils/Logging.h>
#include <glad/glad.h>

using namespace std;

GLVertexArray::GLVertexArray()
    : Buffers()
{
    glGenVertexArrays(1, &BufferID);
}

GLVertexArray::~GLVertexArray()
{
    for (uint32_t i = 0; i < Buffers.size(); i++)
    {
        delete Buffers[i];
    }
}

void GLVertexArray::AddBuffer(Buffer *buf, unsigned int idx)
{
    Bind();
    buf->Bind();

    glEnableVertexAttribArray(idx);
    glVertexAttribPointer(idx, buf->GetComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);

    buf->Unbind();
    Unbind();
}

void GLVertexArray::Bind() const
{
    LOG_INF("Binding VAO: %d\n", BufferID);
    glBindVertexArray(BufferID);
}

void GLVertexArray::Unbind() const
{

    LOG_INF("Unbinding VAO: %d\n", BufferID);
    glBindVertexArray(BufferID);
}

#endif
