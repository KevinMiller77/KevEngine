#ifndef __GL_GENERAL_BUFFER__
#define __GL_GENERAL_BUFFER__

class GLBuffer {
    unsigned int BufferID;
    unsigned int ComponentCount;

public:
    GLBuffer(float* data, int count, unsigned int compCount);
    ~GLBuffer();

    void Bind();
    void Unbind();

    inline unsigned int GetComponentCount() const { return ComponentCount; }
};

#endif
