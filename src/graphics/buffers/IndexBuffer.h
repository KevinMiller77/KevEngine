#ifndef __INDEX_BUFFER__
#define __INDEX_BUFFER__

#include <GL/glew.h>
#include <GL/wglew.h>

class IndexBuffer
{
private:
    GLuint BufferID;
    GLuint Count;

public:
    IndexBuffer::IndexBuffer(GLushort* data, GLsizei count);

    void bind() const;
    void unbind() const;

    inline GLuint getCount() const { return Count; }
};

#endif