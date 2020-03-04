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
    glEnableVertexAttribArray(SHADER_TEXTURE_INDEX);
    glEnableVertexAttribArray(SHADER_TEXTURE_ID_INDEX);

    //Describe our memory map
    glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid *)offsetof(VertexData, VertexData::vertex));
    glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid *)(offsetof(VertexData, VertexData::color)));
    glVertexAttribPointer(SHADER_TEXTURE_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid *)(offsetof(VertexData, VertexData::texture)));
    glVertexAttribPointer(SHADER_TEXTURE_ID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::texID))); 

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
    const GLuint texID = renderable->getTextureID();

    unsigned int c = 0;
    float ts = 0.0f;
    if (texID > 0)
    {
        bool found = false;
        for (int i = 0; i < TextureSlots.size(); i++)
        {
            if (TextureSlots[i] == texID)
            {
                ts = (float)(i + 1);
                found = true;
                break;           
            }
        }

        if (!found)
        {
            if (TextureSlots.size() >= MAX_TEXTURE_SLOTS)
            {
                end();
                draw();
                begin();
            }
            TextureSlots.push_back(texID);
            ts = (float)(TextureSlots.size());
        }
    }
    else
    {
        int r = color.x * 255.0f;
        int g = color.y * 255.0f;
        int b = color.z * 255.0f;
        int a = color.w * 255.0f;

        c = a << 24 | b << 16 | g << 8 | r;
    }


    VDataBuffer->vertex = *curTransformationBack * position;
    VDataBuffer->color = c;
    VDataBuffer->texture = Vec2f(1.0f, 1.0f);
    VDataBuffer->texID = ts;
    VDataBuffer++;

    VDataBuffer->vertex = *curTransformationBack * Vec3f(position.x, position.y + size.y, position.z);
    VDataBuffer->color = c;
    VDataBuffer->texture = Vec2f(1.0f, 0.0f);
    VDataBuffer->texID = ts;
    VDataBuffer++;

    VDataBuffer->vertex = *curTransformationBack * Vec3f(position.x + size.x, position.y + size.y, position.z);
    VDataBuffer->color = c;
    VDataBuffer->texture = Vec2f(0.0f, 0.0f);
    VDataBuffer->texID = ts;
    VDataBuffer++;

    VDataBuffer->vertex = *curTransformationBack * Vec3f(position.x + size.x, position.y, position.z);
    VDataBuffer->color = c;
    VDataBuffer->texture = Vec2f(0.0f, 1.0f);
    VDataBuffer->texID = ts;
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
    for (int tex = 0; tex < TextureSlots.size(); tex++)
    {
        glActiveTexture(GL_TEXTURE0 + tex);
        glBindTexture(GL_TEXTURE_2D, TextureSlots[tex]);
    }

    glBindVertexArray(VAO);
    IBO->bind();

    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, NULL);

    IBO->unbind();
    glBindVertexArray(0);

    indexCount = 0;
}