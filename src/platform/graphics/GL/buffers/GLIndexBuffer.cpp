#include "GLIndexBuffer.h"
#include <glad/glad.h>

GLIndexBuffer::GLIndexBuffer(unsigned int *data, int count)
    : m_Count(count), m_HeapLoc(data)
{

    glGenBuffers(1, &m_BufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

GLIndexBuffer::~GLIndexBuffer()
{
    glDeleteBuffers(1, &m_BufferID);
    free(m_HeapLoc);
}

void GLIndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
}

void GLIndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
