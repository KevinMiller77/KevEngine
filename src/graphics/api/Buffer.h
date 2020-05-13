#ifndef __GENERAL_BUFFER__
#define __GENERAL_BUFFER__

class Buffer {
public:

    virtual void Bind();
    virtual void Unbind();

    virtual unsigned int GetComponentCount() = 0;

    static Buffer* Create(float *data, int count, unsigned int compCount);
};

#endif
