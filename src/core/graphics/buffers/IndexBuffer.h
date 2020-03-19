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

    void Bind() const;
    void Unbind() const;

    inline GLuint GetCount() const { return Count; }
};

#endif