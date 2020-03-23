#ifndef __BETTER_GL_2D_RENDERER__
#define __BETTER_GL_2D_RENDERER__

#include <cstddef>

#include <graphics/renderer/GL2DRenderer.h>
#include <graphics/buffers/IndexBuffer.h>
#include <graphics/buffers/VertexArray.h>

#include <../ext/freetype-gl/freetype-gl.h>

#define RENDERER_MAX_SPRITES 50000
#define RENDERER_VERTEX_SIZE sizeof(VertexData)
#define RENDERER_SPRITE_SIZE (RENDERER_VERTEX_SIZE * 4)
#define RENDERER_BUFFER_SIZE (RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES)
#define RENDERER_INDICIES_SIZE (RENDERER_MAX_SPRITES * 6)

#define MAX_TEXTURE_SLOTS 16

#define SHADER_VERTEX_INDEX 0
#define SHADER_COLOR_INDEX 1
#define SHADER_TEXTURE_INDEX 2
#define SHADER_TEXTURE_ID_INDEX 3

class VertexData;

class Kev2DRenderer : public GL2DRenderer
{
private:
    unsigned int VAO;
    unsigned int VBO;
    IndexBuffer *IBO;
    int indexCount;
    VertexData *VDataBuffer;
    VertexData *VDataHeapLoc = nullptr;

    std::vector<unsigned int> TextureSlots;

public:
    Kev2DRenderer();
    ~Kev2DRenderer() override;

    void Submit(const Renderable2D *renderable) override;
    void Draw() override;
    void DrawString(std::string text, Vec3f position, FontInfo* font, uint32_t color) override;
    void Begin();
    void End();

private:
    void Init();
};

#endif