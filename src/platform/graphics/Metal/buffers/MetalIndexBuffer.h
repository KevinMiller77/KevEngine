#ifndef __METAL_INDEX_BUFFER__
#define __METAL_INDEX_BUFFER__
#include <cstdlib>

#include <graphics/api/IndexBuffer.h>
#include <platform/graphics/Metal/Metal.h>

class MetalIndexBuffer : public IndexBuffer
{
private:
    id <MTLBuffer> m_Buffer;
    unsigned int m_Count;

public:
    MetalIndexBuffer(unsigned int *Data, int Count);
    ~MetalIndexBuffer();

    virtual void Bind() const override;
    virtual void Unbind() const override;
    
    inline virtual void* GetBuffer() override { return (void*)&m_Buffer; }
    inline virtual id<MTLBuffer> GetMetalBuffer() { return m_Buffer; }
    
    inline unsigned int GetCount() const override { return m_Count; }
};

#endif
