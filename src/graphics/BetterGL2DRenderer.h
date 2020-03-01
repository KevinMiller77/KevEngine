#ifndef __BETTER_GL_2D_RENDERER__
#define __BETTER_GL_2D_RENDERER__

#include "GL2DRenderer.h"
#include "buffers/VertexArray.h"

#define RENDERER_MAX_SPRITES 10000
#define RENDERER_VERTEX_SIZE sizeof(VertexData)
#define RENDERER_SPRITE_SIZE (RENDERER_VERTEX_SIZE * 4)
#define RENDERER_BUFFER_SIZE (RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES)
#define RENDERER_INDICIES_SIZE (RENDERER_MAX_SPRITES * 6)

#define SHADER_VERTEX_INDEX 0
#define SHADER_COLOR_INDEX 1
#define SHADER_TEXTURE_INDEX 2

class BetterGL2DRenderer
{
private:
    GLuint VAO;
    IndexBuffer *IBO;
    GLsizei indexCount;
    GLuint VBO;

    std::deque<const Renderable2D *> RenderQueue;

public:
    BetterGL2DRenderer();
    ~BetterGL2DRenderer();
    void submit(const Renderable2D *renderable);
    void flush();
    void draw();

private:
    void init();
};

#endif