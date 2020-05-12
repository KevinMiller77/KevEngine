#include "GLIndexBuffer.h"
#include <glad/glad.h>

GLIndexBuffer::GLIndexBuffer(unsigned int *data, int count)
    : Count(count), HeapLoc(data)
{

    glGenBuffers(1, &BufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

GLIndexBuffer::~GLIndexBuffer()
{
    glDeleteBuffers(1, &BufferID);
    free(HeapLoc);
}

void GLIndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferID);
}

void GLIndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
