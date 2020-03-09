#include "Layer.h"

Layer::Layer(Renderer2D *renderer, GLuint shader, Mat4f projMatrix)
    : Renderer(renderer), Shader(shader), projectionMatrix(projMatrix), enabled(true)
{
    ShaderProgram::enableShaderProgram(Shader);
    ShaderProgram::setShaderUniformMat4(Shader, "pr_matrix", projectionMatrix);
    ShaderProgram::disableShaderProgram();
}

Layer::~Layer()
{
    delete Renderer;

    for (Renderable2D* renderable : renderables)
    {
        delete renderable;
    }
}

void Layer::add(Renderable2D *renderable)
{
    renderables.push_back(renderable);
}

void Layer::render()
{
    if (enabled)
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
}
