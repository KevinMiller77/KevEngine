#include "MetalBuffer.h"
#include <string>

MetalRawBuffer::MetalRawBuffer(int SizeInBytes)
    : m_ComponentCount(SizeInBytes)
{
    id <MTLDevice> device = GET_METAL_DEVICE();
    m_Buffer = [device newBufferWithLength:(SizeInBytes)
                    options:MTLResourceOptionCPUCacheModeDefault];
}
MetalRawBuffer::MetalRawBuffer(float* Data, int NumComponents)
    : m_ComponentCount(NumComponents)
{
    id <MTLDevice> device = GET_METAL_DEVICE();
    m_Buffer = [device newBufferWithBytes:Data
                    length:(sizeof(float) * NumComponents)
                    options:MTLResourceOptionCPUCacheModeDefault];
}

MetalRawBuffer::~MetalRawBuffer()
{
    m_Buffer = 0;
}

void MetalRawBuffer::Bind()
{
    
}

void MetalRawBuffer::Unbind()
{
    
}
