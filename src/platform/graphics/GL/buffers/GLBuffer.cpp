#include "GLBuffer.h"
#include <glad/glad.h>

GLBuffer::GLBuffer(float *data, int count, unsigned int compCount)
    : ComponentCount(compCount)
{

    glGenBuffers(1, &BufferID);
    glBindBuffer(GL_ARRAY_BUFFER, BufferID);
    glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GLBuffer::~GLBuffer()
{
    glDeleteBuffers(1, &BufferID);
}

void GLBuffer::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, BufferID);
}

void GLBuffer::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, BufferID);
}
