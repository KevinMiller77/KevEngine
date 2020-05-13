#ifndef __BETTER_GL_2D_RENDERER__
#define __BETTER_GL_2D_RENDERER__

#include <cstddef>

#include <graphics/api/Renderer2D.h>
#include <platform/graphics/GL/buffers/GLIndexBuffer.h>
#include <platform/graphics/GL/buffers/GLVertexArray.h>
#include <platform/graphics/GL/buffers/GLFrameBuffer.h>
#include <platform/graphics/GL/renderer/GLTextureProgram.h>

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
#define SHADER_ML_MAT_INDEX 4

class VertexData;

class GLRenderer2D : public Renderer2D
{
private:
    int *scr_w;
    int *scr_h;

    unsigned int VAO;
    unsigned int VBO;
    unsigned int curShader;
    GLIndexBuffer *IBO;
    int indexCount;
    VertexData *VDataBuffer;
    VertexData *VDataHeapLoc = nullptr;
    GLFrameBuffer* FBO;

    std::vector<unsigned int> TextureSlots;

public:
    GLRenderer2D(int* width, int* height);
    ~GLRenderer2D();

    virtual void Submit(Renderable2D *Renderable, const Vec2u TilesheetPos = Vec2u(0, 0)) override;
    virtual void Draw() override;
    virtual unsigned int DrawToBuffer() override;
    virtual void DrawString(std::string text, Vec3f position, FontInfo* font, uint32_t color) override;
    virtual void Begin(unsigned int Shader) override;
    virtual void End() override;

private:
    void Init();
};

#endif
