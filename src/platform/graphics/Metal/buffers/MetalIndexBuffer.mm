#include "MetalIndexBuffer.h"
#include <platform/graphics/Metal/Metal.h>
#include <platform/graphics/Metal/renderer/MetalContext.h>

MetalIndexBuffer::MetalIndexBuffer(unsigned int *Data, int Count)
    : m_Count(Count)
{
    id <MTLDevice> device = GET_METAL_DEVICE();
    m_Buffer = [device newBufferWithBytes:Data
                   length:(sizeof(unsigned int) * Count)
                  options:MTLResourceOptionCPUCacheModeDefault];
}

MetalIndexBuffer::~MetalIndexBuffer()
{
    m_Buffer = 0;
}

void MetalIndexBuffer::Bind() const
{
}

void MetalIndexBuffer::Unbind() const
{
}
