#ifndef __GENERAL_BUFFER__
#define __GENERAL_BUFFER__

class Buffer {
public:
    virtual void Bind() = 0;
    virtual void Unbind() = 0;

    virtual void* GetBuffer() = 0;
    virtual unsigned int GetComponentCount() = 0;

    static Buffer* Create(float *Data, int Count, unsigned int NumComponents);
};

#endif
