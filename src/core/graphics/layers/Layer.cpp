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
