#ifndef __GENERAL_BUFFER__
#define __GENERAL_BUFFER__

class Buffer {
    unsigned int BufferID;
    unsigned int ComponentCount;

public:
    Buffer(float* data, int count, unsigned int compCount);
    ~Buffer();

    void Bind();
    void Unbind();

    inline unsigned int GetComponentCount() const { return ComponentCount; }
};

#endif