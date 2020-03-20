#include "Buffer.h"
#include <glad/glad.h>

Buffer::Buffer(float *data, int count, unsigned int compCount)
    : ComponentCount(compCount)
{

    glGenBuffers(1, &BufferID);
    glBindBuffer(GL_ARRAY_BUFFER, BufferID);
    glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Buffer::~Buffer()
{
    glDeleteBuffers(1, &BufferID);
}

void Buffer::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, BufferID);
}

void Buffer::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, BufferID);
}