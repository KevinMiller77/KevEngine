#include "MetalRenderer2D.h"

#include "MetalShaderProgram.h"
#include <graphics/renderables/Renderable2D.h>

#include <platform/graphics/Metal/Metal.h>

MetalRenderer2D::MetalRenderer2D(int* width, int* height)
    : scr_w(width), scr_h(height), m_IndexBuffer(nullptr)
{
    Init();
}

MetalRenderer2D::~MetalRenderer2D()
{
    // delete IBO;
    // MetalDeleteVertexArrays(1, &VAO);
    // MetalDeleteBuffers(1, &VBO);
}

void MetalRenderer2D::Init()
{
    // //Generate all of the necessary spaces in memory
    // MetalGenVertexArrays(1, &VAO);
    // MetalGenBuffers(1, &VBO);

    // //Bind the buffers used
    // MetalBindVertexArray(VAO);
    // MetalBindBuffer(Metal_ARRAY_BUFFER, VBO);
    // MetalBufferData(Metal_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, Metal_DYNAMIC_DRAW);

    // //Enable the attributes our renderer will use (vertex, color, texture, etc.)
    // MetalEnableVertexAttribArray(SHADER_VERTEX_INDEX);
    // MetalEnableVertexAttribArray(SHADER_COLOR_INDEX);
    // MetalEnableVertexAttribArray(SHADER_TEXTURE_INDEX);
    // MetalEnableVertexAttribArray(SHADER_TEXTURE_ID_INDEX);

    // //Describe our memory map
    // MetalVertexAttribPointer(SHADER_VERTEX_INDEX, 3, Metal_FLOAT, Metal_FALSE, RENDERER_VERTEX_SIZE, (const Metalvoid *)(0));
    // MetalVertexAttribPointer(SHADER_TEXTURE_INDEX, 2, Metal_FLOAT, Metal_TRUE, RENDERER_VERTEX_SIZE, (const Metalvoid *)(12));
    // MetalVertexAttribPointer(SHADER_TEXTURE_ID_INDEX, 1, Metal_FLOAT, Metal_FALSE, RENDERER_VERTEX_SIZE, (const Metalvoid*)(20));
    // MetalVertexAttribPointer(SHADER_COLOR_INDEX, 4, Metal_UNSIGNED_BYTE, Metal_TRUE, RENDERER_VERTEX_SIZE, (const Metalvoid *)(24));
    
    m_VertexBuffer = new MetalRawBuffer(RENDERER_BUFFER_SIZE);
    unsigned int *indicies = new unsigned int[RENDERER_INDICIES_SIZE];

     unsigned int offset = 0;
     for (int i = 0; i < RENDERER_INDICIES_SIZE; i += 6)
     {
         indicies[i + 0] = offset + 0;
         indicies[i + 1] = offset + 1;
         indicies[i + 2] = offset + 2;
         indicies[i + 3] = offset + 2;
         indicies[i + 4] = offset + 3;
         indicies[i + 5] = offset + 0;

         offset += 4;
     }
    
    m_IndexBuffer = new MetalIndexBuffer(indicies, RENDERER_INDICIES_SIZE);
}

void MetalRenderer2D::Begin(void* Shader)
{
    id<MTLBuffer> VBO = m_VertexBuffer->GetMetalBuffer();
    VDataBuffer = (VertexData*)[VBO contents];
    VDataHeapLoc = VDataHeapLoc ? VDataHeapLoc : VDataBuffer;
    
    m_Drawable = [GET_METAL_LAYER() nextDrawable];
    
    m_RenderPassDescriptor = [MTLRenderPassDescriptor renderPassDescriptor];
    m_RenderPassDescriptor.colorAttachments[0].texture = m_Drawable.texture;
    m_RenderPassDescriptor.colorAttachments[0].loadAction = MTLLoadActionClear;
    m_RenderPassDescriptor.colorAttachments[0].clearColor = MTLClearColorMake(1, 1, 1, 1);
    m_RenderPassDescriptor.colorAttachments[0].storeAction = MTLStoreActionStore;
    
    m_CommandBuffer = [GET_METAL_QUEUE() commandBuffer];
    
    m_RenderEncoder = [m_CommandBuffer renderCommandEncoderWithDescriptor:m_RenderPassDescriptor];
    id<MTLRenderPipelineState> pipelineState = *((id<MTLRenderPipelineState>*)Shader);

    [m_RenderEncoder setRenderPipelineState:pipelineState];
    
}

void MetalRenderer2D::Submit(Renderable2D *Renderable, const Vec2u TilesheetPos)
{
    const Vec3f position = Renderable->GetPosition();
    const Vec2f size = Renderable->GetSize();
    const uint32_t color = Renderable->GetColor();
    const unsigned int texID = Renderable->GetTextureID();
//
//    bool texExists = false;
//
//    if (Renderable->GetTexturePtr() != nullptr)
//    {
//       texExists = true;
//    }
//    
    float ts = 0.0f;
//    if (texID > 0)
//    {
//        bool found = false;
//        for (unsigned int i = 0; i < TextureSlots.size(); i++)
//        {
//            if (TextureSlots[i] == texID)
//            {
//                
//                ts = (float)(i + 1);
//                found = true;
//                break;           
//            }
//        }
//
//        if (!found)
//        {
//            if (TextureSlots.size() >= MAX_TEXTURE_SLOTS)
//            {
//                End();
//                Draw();
//                Begin(curShader);
//            }
//            TextureSlots.push_back(texID);
//            ts = (float)(TextureSlots.size());
//            LOG_INF("New texture slot. Using %d\n", (int)ts);
//        }
//    }
//
    Vec2f tex_BL = Vec2f(1.0f, 1.0f), tex_BR = Vec2f(1.0f, 0.0f), tex_TR = Vec2f(0.0f, 0.0f), tex_TL = Vec2f(0.0f, 1.0f);
//
//    if (texExists)
//    {
//        TextureProgram* tex = Renderable->GetTexturePtr();
//        if (tex->IsTilesheet())
//        {
//            Vec2u pos = Renderable->GetTilesheetPos();
//            float sheetWidth = tex->GetWidth(), sheetHeight = tex->GetHeight();
//            float tileSize = tex->GetTileSize();
//
//            tex_BR = Vec2f((pos.x * tileSize) / sheetWidth, ((pos.y * tileSize) / sheetHeight));
//            tex_TR = Vec2f(((pos.x + 1) * tileSize) / sheetWidth, ((pos.y * tileSize) / sheetHeight));
//            tex_TL = Vec2f(((pos.x + 1) * tileSize) / sheetWidth, (((pos.y + 1) * tileSize) / sheetHeight));
//            tex_BL = Vec2f((pos.x * tileSize) / sheetWidth, (((pos.y + 1) * tileSize) / sheetHeight));
//        }
//    }
//    
//    
    VDataBuffer->vertex = *curTransformationBack * position;
    VDataBuffer->color = color;
    VDataBuffer->texture = tex_BL;
    VDataBuffer->texID = ts;
    VDataBuffer++;
    
    VDataBuffer->vertex = *curTransformationBack * Vec3f(position.x, position.y + size.y, position.z);
    VDataBuffer->color = color;
    VDataBuffer->texture = tex_BR;
    VDataBuffer->texID = ts;
    VDataBuffer++;

    VDataBuffer->vertex = *curTransformationBack * Vec3f(position.x + size.x, position.y + size.y, position.z);
    VDataBuffer->color = color;
    VDataBuffer->texture = tex_TR;
    VDataBuffer->texID = ts;
    VDataBuffer++;

    VDataBuffer->vertex = *curTransformationBack * Vec3f(position.x + size.x, position.y, position.z);
    VDataBuffer->color = color;
    VDataBuffer->texture = tex_TL;
    VDataBuffer->texID = ts;
    VDataBuffer++;

    m_IndexCount += 6;
}

void MetalRenderer2D::DrawString(std::string text, Vec3f position, KevFontInfo* font, uint32_t color)
{
    // using namespace ftMetal;

    // float ts = 0.0f;
    // bool found = false;
    // for (unsigned int i = 0; i < TextureSlots.size(); i++)
    // {
    //     if (TextureSlots[i] == font->atlas->id)
    //     {
            
    //         ts = (float)(i + 1);
    //         found = true;
    //         break;           
    //     }
    // }
    // if (!found)
    // {
    //     if (TextureSlots.size() >= MAX_TEXTURE_SLOTS)
    //     {
    //         End();
    //         Draw();
    //         Begin(curShader);
    //     }
    //     TextureSlots.push_back(font->atlas->id);
    //     ts = (float)(TextureSlots.size());
    // }

    // float scaleX = 960.0f / 32.0f;
	// float scaleY = 540.0f / 18.0f;  

    // float x = position.x;

    // for (int i = 0; i < text.length(); i++)
    // {
    //     char c = text[i];
    //     texture_Metalyph_t* Metalyph = texture_font_get_Metalyph(font->font, c);
    //     if (Metalyph != NULL)
    //     {

    //         float x0 = x + Metalyph->offset_x / scaleX;
    //         float y0 = position.y + (Metalyph->height - Metalyph->offset_y) / scaleY;
    //         float x1 = x0 + Metalyph->width / scaleX;
    //         float y1 = y0 - Metalyph->height / scaleY;                

    //         float u0 = Metalyph->s0;
    //         float v0 = Metalyph->t1;
    //         float u1 = Metalyph->s1;
    //         float v1 = Metalyph->t0;
            
    //         VDataBuffer->vertex = *curTransformationBack * Vec3f(x0, y0, 0);
    //         VDataBuffer->texture = Vec2f(u0, v0);
    //         VDataBuffer->texID = ts;
    //         VDataBuffer->color = color;
    //         VDataBuffer++;

    //         VDataBuffer->vertex = *curTransformationBack * Vec3f(x0, y1, 0);
    //         VDataBuffer->texture = Vec2f(u0, v1);
    //         VDataBuffer->texID = ts;
    //         VDataBuffer->color = color;
    //         VDataBuffer++;

    //         VDataBuffer->vertex = *curTransformationBack * Vec3f(x1, y1, 0);
    //         VDataBuffer->texture = Vec2f(u1, v1);
    //         VDataBuffer->texID = ts;
    //         VDataBuffer->color = color;
    //         VDataBuffer++;

    //         VDataBuffer->vertex = *curTransformationBack * Vec3f(x1, y0, 0);
    //         VDataBuffer->texture = Vec2f(u1, v0);
    //         VDataBuffer->texID = ts;
    //         VDataBuffer->color = color;
    //         VDataBuffer++;

    //         indexCount += 6;

    //         x += Metalyph->advance_x / scaleX;
    //     }

    // }
}

void MetalRenderer2D::End()
{
    
    // //Describe our memory map
    // MetalVertexAttribPointer(SHADER_VERTEX_INDEX, 3, Metal_FLOAT, Metal_FALSE, RENDERER_VERTEX_SIZE, (const Metalvoid *)(0));
    // MetalVertexAttribPointer(SHADER_TEXTURE_INDEX, 2, Metal_FLOAT, Metal_TRUE, RENDERER_VERTEX_SIZE, (const Metalvoid *)(12));
    // MetalVertexAttribPointer(SHADER_TEXTURE_ID_INDEX, 1, Metal_FLOAT, Metal_FALSE, RENDERER_VERTEX_SIZE, (const Metalvoid*)(20));
    // MetalVertexAttribPointer(SHADER_COLOR_INDEX, 4, Metal_UNSIGNED_BYTE, Metal_TRUE, RENDERER_VERTEX_SIZE, (const Metalvoid *)(24));
    
    id<MTLBuffer> VBO = m_VertexBuffer->GetMetalBuffer();
    [m_RenderEncoder setVertexBuffer:VBO offset:0 atIndex:0];
    
    [m_RenderEncoder drawIndexedPrimitives:MTLPrimitiveTypeTriangle indexCount:6 indexType:MTLIndexTypeUInt32 indexBuffer:m_IndexBuffer->GetMetalBuffer() indexBufferOffset:0 instanceCount:(6)];
}

unsigned int MetalRenderer2D::DrawToBuffer()
{
    // MetalBindVertexArray(VAO);
    // IBO->Bind();
    
    // MetalDrawElements(Metal_TRIANMetalES, indexCount, Metal_UNSIGNED_INT, NULL);

    // IBO->Unbind();
    // MetalBindVertexArray(0);

    return 0;
}

void MetalRenderer2D::Draw()
{
    [m_RenderEncoder endEncoding];
    
    [m_CommandBuffer presentDrawable:m_Drawable];
    [m_CommandBuffer commit];
}


