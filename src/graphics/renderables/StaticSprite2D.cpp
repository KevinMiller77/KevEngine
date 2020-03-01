#include "StaticSprite2D.h"

StaticSprite::StaticSprite(char *ID, GLuint shaderProg, float x, float y, float width, float height, Vec4f color, char *texLocation)
    : Renderable2D((const char *)ID, Vec3f(x, y, 0), Vec2f(width, height), color, shaderProg)
{
    pos = Vec3f(x, y, 0);
    size = Vec2f(width, height);

    VAO = new VertexArray();

    GLfloat vertices[] =
        {
            0.0f, 0.0f, 0.0f,
            0.0f, height, 0.0f,
            width, height, 0.0f,
            width, 0.0f, 0.0f};

    GLfloat colors[] =
        {
            Color.x, Color.y, Color.z, Color.w,
            Color.x, Color.y, Color.z, Color.w,
            Color.x, Color.y, Color.z, Color.w,
            Color.x, Color.y, Color.z, Color.w};

    GLfloat texVerticies[] = {
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f};

    //Set specific shader info
    VAO->addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
    VAO->addBuffer(new Buffer(colors, 4 * 4, 4), 1);
    //VAO->addBuffer(new Buffer(texVerticies, 4 * 2, 2), 2);

    if (texLocation != nullptr)
    {
        LOG_INF("Loading texture\n");
        LoadTexture(texLocation);
    }

    GLushort indices[] = {0, 1, 2, 2, 3, 0};
    IBO = new IndexBuffer(indices, 6);
}
