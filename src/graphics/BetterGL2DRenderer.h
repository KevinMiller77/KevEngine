#ifndef __BETTER_GL_2D_RENDERER__
#define __BETTER_GL_2D_RENDERER__

#include "GL2DRenderer.h"
#include "buffers/VertexArray.h"
#include <cstddef>

#define USING_TEXTURES 0

#define RENDERER_MAX_SPRITES 60000
#define RENDERER_VERTEX_SIZE sizeof(VertexData)
#define RENDERER_SPRITE_SIZE (RENDERER_VERTEX_SIZE * 4)
#define RENDERER_BUFFER_SIZE (RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES)
#define RENDERER_INDICIES_SIZE (RENDERER_MAX_SPRITES * 6)

#define SHADER_VERTEX_INDEX 0
#define SHADER_COLOR_INDEX 1

#if USING_TEXTURES
#define SHADER_TEXTURE_INDEX 2
#endif

class BetterGL2DRenderer : public GL2DRenderer
{
private:
    GLuint VAO;
    GLuint VBO;
    IndexBuffer *IBO;
    GLsizei indexCount;
    VertexData *VDataBuffer;

public:
    BetterGL2DRenderer();
    ~BetterGL2DRenderer();
    void begin();
    void submit(const Renderable2D *renderable) override;
    void end();
    void draw() override;

private:
    void init();
};

#endif