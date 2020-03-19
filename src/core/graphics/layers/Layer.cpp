#include "Layer.h"

Layer::Layer(GL2DRenderer *renderer, GLuint shader)
    : Renderer(renderer), Shader(shader), enabled(true)
{
}

Layer::~Layer()
{
    delete Renderer;

    for (Renderable2D* renderable : renderables)
    {
        delete renderable;
    }
}

void Layer::Add(Renderable2D *renderable)
{
    renderables.push_back(renderable);
}

void Layer::Render()
{
    if (enabled)
    {
        ShaderProgram::EnableShaderProgram(Shader);
        Renderer->Begin();

        for (Renderable2D *renderable : renderables)
        {
            renderable->Submit(Renderer);
        }
        
        Renderer->End();   
        Renderer->Draw();
    }
}
