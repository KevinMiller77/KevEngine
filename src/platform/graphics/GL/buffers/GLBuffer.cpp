#include "GLBuffer.h"
#include <glad/glad.h>

GLBuffer::GLBuffer(float *Data, int NumComponents)
    : m_ComponentCount(NumComponents)
{

    glGenBuffers(1, &m_BufferID);
    glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
    glBufferData(GL_ARRAY_BUFFER, NumComponents * sizeof(float), Data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GLBuffer::~GLBuffer()
{
    glDeleteBuffers(1, &m_BufferID);
}

void GLBuffer::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
}

void GLBuffer::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
}
