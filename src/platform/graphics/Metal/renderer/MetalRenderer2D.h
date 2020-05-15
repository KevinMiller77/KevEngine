#ifndef __METAL_2D_RENDERER__
#define __METAL_2D_RENDERER__

#include <cstddef>

#include <graphics/api/Renderer2D.h>
#include <platform/graphics/Metal/buffers/MetalIndexBuffer.h>
#include <platform/graphics/Metal/buffers/MetalVertexArray.h>
#include <platform/graphics/Metal/buffers/MetalFrameBuffer.h>
#include <platform/graphics/Metal/renderer/MetalTextureProgram.h>

class VertexData;

class MetalRenderer2D : public Renderer2D
{
private:
    int *scr_w;
    int *scr_h;
    
    int m_IndexCount = 0;

    MetalRawBuffer* m_VertexBuffer;
    MetalIndexBuffer* m_IndexBuffer;
    
    id<CAMetalDrawable> m_Drawable;
    id<MTLCommandBuffer> m_CommandBuffer;
    id<MTLRenderCommandEncoder> m_RenderEncoder;
    MTLRenderPassDescriptor* m_RenderPassDescriptor;
    
    VertexData *VDataBuffer;
    VertexData *VDataHeapLoc = nullptr;
    std::vector<unsigned int> TextureSlots;

public:
    MetalRenderer2D(int* width, int* height);
    ~MetalRenderer2D();

    virtual void Submit(Renderable2D *Renderable, const Vec2u TilesheetPos = Vec2u(0, 0)) override;
    virtual void Draw() override;
    virtual unsigned int DrawToBuffer() override;
    virtual void DrawString(std::string text, Vec3f position, KevFontInfo* font, uint32_t color) override;
    virtual void Begin(void* Shader) override;
    virtual void End() override;

private:
    void Init();
};

#endif
