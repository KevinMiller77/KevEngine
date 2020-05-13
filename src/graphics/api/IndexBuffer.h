#ifndef __INDEX_BUFFER__
#define __INDEX_BUFFER__

class IndexBuffer
{
public:
    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual unsigned int GetCount() const = 0;

    static IndexBuffer* Create(unsigned int *data, int count);
};

#endif
