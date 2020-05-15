#ifndef __METAL_VERT_ARRAY__
#define __METAL_VERT_ARRAY__
#include <vector>
#include "MetalBuffer.h"

#include <graphics/api/VertexArray.h>
#include <platform/graphics/Metal/Metal.h>

class MetalVertexArray : public VertexArray
{
private:
    std::vector<MetalRawBuffer*> m_Buffers;

public:
    MetalVertexArray();
    ~MetalVertexArray();

    virtual void AddBuffer(Buffer* buf, unsigned int idx) override;
    virtual void Bind() const override;
    virtual void Unbind() const override;
};
#endif
