#ifndef __VERTEX_ARRAY__
#define __VERTEX_ARRAY__
#include "MetalVertexArray.h"
#include <utils/Logging.h>

using namespace std;

MetalVertexArray::MetalVertexArray()
    : m_Buffers()
{
}

MetalVertexArray::~MetalVertexArray()
{
    for (uint32_t i = 0; i < m_Buffers.size(); i++)
    {
        id<MTLBuffer>* buf = (id<MTLBuffer>*)m_Buffers[i]->GetBuffer();
        *buf = 0;
    }
}

void MetalVertexArray::AddBuffer(Buffer *buf, unsigned int idx)
{
    //TODO: Metal add buffer
    m_Buffers.push_back((MetalRawBuffer*)buf);
}

void MetalVertexArray::Bind() const
{
}

void MetalVertexArray::Unbind() const
{
}

#endif
