#include "BetterGL2DRenderer.h"

BetterGL2DRenderer::BetterGL2DRenderer()
{
    indexCount = 0;
    init();
}

BetterGL2DRenderer::~BetterGL2DRenderer()
{
    delete IBO;
    glDeleteBuffers(1, &VBO);
}

void BetterGL2DRenderer::init()
{
    //Generate all of the necessary spaces in memory
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    //Bind the buffers used
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

    //Enable the attributes our renderer will use (vertex, color, texture, etc.)
    glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
    glEnableVertexAttribArray(SHADER_COLOR_INDEX);
#if USING_TEXTURES
    glEnableVertexArrayAttrib(SHADER_TEXTURE_INDEX);
#endif

    //Describe our memory map
    glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid *)offsetof(VertexData, VertexData::vertex));
    glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid *)(offsetof(VertexData, VertexData::color)));
#if USING_TEXTURES
    glVertexAttribPointer(SHADER_TEXTURE_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid *)(offsetof(VertexData, VertexData::texture)));
#endif

    //Unbind VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //Generate Index Buffer data for drawing pleasure
    GLuint *indicies = new GLuint[RENDERER_INDICIES_SIZE];

    GLuint offset = 0;
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

    //Fill an Index buffer with the generated data
    IBO = new IndexBuffer(indicies, RENDERER_INDICIES_SIZE);

    //Unbind VAO
    glBindVertexArray(0);
}

void BetterGL2DRenderer::begin()
{
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    VDataBuffer = (VertexData *)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
}

void BetterGL2DRenderer::submit(const Renderable2D *renderable)
{
    const Vec3f position = renderable->getPosition();
    const Vec2f size = renderable->getSize();
    const Vec4f color = renderable->getColor();

    //LOG_INF("New square, base index : %d\nSize %f, %f\nVertex one: %f, %f\nVertex two: %f, %f\nVertex three: %f, %f\nVertex four: %f, %f\n\n",
    //indexCount, size.x, size.y, position.x, position.y, position.x, position.y + size.y, position.x + size.x, position.y + size.y, position.x + size.x, position.y);

    VDataBuffer->vertex = position;
    VDataBuffer->color = color;
#if USING_TEXTURES
    VDataBuffer->texture = Vec2f(1.0f, 1.0f);
#endif
    VDataBuffer++;

    VDataBuffer->vertex = Vec3f(position.x, position.y + size.y, position.z);
    VDataBuffer->color = color;
#if USING_TEXTURES
    VDataBuffer->texture = Vec2f(1.0f, 0.0f);
#endif
    VDataBuffer++;

    VDataBuffer->vertex = Vec3f(position.x + size.x, position.y + size.y, position.z);
    VDataBuffer->color = color;
#if USING_TEXTURES
    VDataBuffer->texture = Vec2f(0.0f, 0.0f);
#endif
    VDataBuffer++;

    VDataBuffer->vertex = Vec3f(position.x + size.x, position.y, position.z);
    VDataBuffer->color = color;
#if USING_TEXTURES
    VDataBuffer->texture = Vec2f(0.0f, 1.0f);
#endif
    VDataBuffer++;

    indexCount += 6;
}

void BetterGL2DRenderer::end()
{
    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void BetterGL2DRenderer::draw()
{
    glBindVertexArray(VAO);
    IBO->bind();

    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, NULL);

    IBO->unbind();
    glBindVertexArray(0);

    indexCount = 0;
}