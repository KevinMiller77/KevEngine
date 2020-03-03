#include "StaticSprite2D.h"

StaticSprite::StaticSprite(float x, float y, float width, float height, Vec4f color, ShaderProgram* inShader)
    : Renderable2D(Vec3f(x, y, 0), Vec2f(width, height), color), shader(inShader)
{
    VAO = new VertexArray();

    GLfloat vertices[] =
        {
            0.0f, 0.0f, 0.0f,
            0.0f, height, 0.0f,
            width, height, 0.0f,
            width, 0.0f, 0.0f};

    GLfloat colors[] =
        {
            color.x, color.y, color.z, color.w,
            color.x, color.y, color.z, color.w,
            color.x, color.y, color.z, color.w,
            color.x, color.y, color.z, color.w};

    //Set specific shader info
    VAO->addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
    VAO->addBuffer(new Buffer(colors, 4 * 4, 4), 1);

    GLuint indices[] = {0, 1, 2, 2, 3, 0};
    IBO = new IndexBuffer(indices, 6);
}
