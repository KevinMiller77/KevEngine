#ifndef __GENERAL_BUFFER__
#define __GENERAL_BUFFER__

#include <GL/glew.h>

class Buffer {
    GLuint BufferID;
    GLuint ComponentCount;

public:
    Buffer(GLfloat* data, GLsizei count, GLuint compCount);
    ~Buffer();

    void bind();
    void unbind();

    inline GLuint getComponentCount() const { return ComponentCount; }
};

#endif