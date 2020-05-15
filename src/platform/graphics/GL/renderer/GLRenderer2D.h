#ifndef __BETTER_GL_2D_RENDERER__
#define __BETTER_GL_2D_RENDERER__

#include <cstddef>

#include <graphics/api/Renderer2D.h>
#include <platform/graphics/GL/buffers/GLIndexBuffer.h>
#include <platform/graphics/GL/buffers/GLVertexArray.h>
#include <platform/graphics/GL/buffers/GLFrameBuffer.h>
#include <platform/graphics/GL/renderer/GLTextureProgram.h>

#include <../ext/freetype-gl/freetype-gl.h>

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
    virtual void DrawString(std::string text, Vec3f position, KevFontInfo* font, uint32_t color) override;
    virtual void Begin(void* Shader) override;
    virtual void End() override;

private:
    void Init() override;
};

#endif
