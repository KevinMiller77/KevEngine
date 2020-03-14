#ifndef __INDEX_BUFFER__
#define __INDEX_BUFFER__
#include <cstdlib>
#include <GL/glew.h>

#ifdef WIN32
#include <GL/wglew.h>
#endif

class IndexBuffer
{
private:
    GLuint BufferID;
    GLuint Count;
    GLuint* HeapLoc;

public:
    IndexBuffer(GLuint *data, GLsizei count);
    ~IndexBuffer();

    void bind() const;
    void unbind() const;

    inline GLuint getCount() const { return Count; }
};

#endif