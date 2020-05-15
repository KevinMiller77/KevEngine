#ifndef __METAL_GENERAL_BUFFER__
#define __METAL_GENERAL_BUFFER__
#include <graphics/api/Buffer.h>
#include <platform/graphics/Metal/Metal.h>

class MetalRawBuffer : public Buffer {
    id <MTLBuffer> m_Buffer;
    unsigned int m_ComponentCount;

public:
    MetalRawBuffer(int SizeInBytes);
    MetalRawBuffer(float* Data, int NumComponents);
    ~MetalRawBuffer();

    virtual void Bind() override;
    virtual void Unbind() override;
    
    inline virtual void* GetBuffer() override { return (void*)&m_Buffer; }
    inline id<MTLBuffer> GetMetalBuffer() { return m_Buffer; }
    
    virtual unsigned int GetComponentCount() override { return m_ComponentCount; }
};

#endif
