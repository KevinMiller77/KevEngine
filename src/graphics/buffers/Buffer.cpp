#include "Buffer.h"

Buffer::Buffer(GLfloat* data, GLsizei count, GLuint compCount)
    :   ComponentCount(compCount)
{

    glGenBuffers(1, &BufferID);
    glBindBuffer(GL_ARRAY_BUFFER, BufferID);
    glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Buffer::bind(){
    glBindBuffer(GL_ARRAY_BUFFER, BufferID);
}

void Buffer::unbind(){
    glBindBuffer(GL_ARRAY_BUFFER, BufferID);
}