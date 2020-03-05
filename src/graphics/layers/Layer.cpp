#include "Layer.h"

Layer::Layer(GL2DRenderer *renderer, GLuint shader, Mat4f projMatrix)
    : Renderer(renderer), Shader(shader), projectionMatrix(projMatrix)
{
    texture = new Texture();
    ShaderProgram::enableShaderProgram(Shader);
    ShaderProgram::setShaderUniformMat4(Shader, "pr_matrix", projectionMatrix);
    ShaderProgram::disableShaderProgram();
}

Layer::~Layer()
{
    delete Renderer;

    for (int i = 0; i < renderables.size(); i++)
    {
        delete renderables[i];
    }
}

void Layer::add(Renderable2D *renderable)
{
    renderables.push_back(renderable);
}

void Layer::render()
{
    ShaderProgram::enableShaderProgram(Shader);
    Renderer->begin();

    for (Renderable2D *renderable : renderables)
    {
        renderable->submit(Renderer);
    }

    Renderer->end();   
    Renderer->draw();
}
