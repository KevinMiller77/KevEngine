#include "Layer.h"

Layer::Layer(Window* Parent, GL2DRenderer *Renderer, unsigned int Shader)
    : parent(Parent), renderer(Renderer), shader(Shader), enabled(true)
{
    keyDebounce.Start();
}

Layer::~Layer()
{
    delete renderer;

    for (Renderable2D* renderable : renderables)
    {
#ifdef KEV_PLATFORM_MACOS
        
#else
        delete renderable;
#endif
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
        ShaderProgram::EnableShaderProgram(shader);
        renderer->Begin();

        for (Renderable2D *renderable : renderables)
        {
            renderable->Submit(renderer);
        }
        
        renderer->End();   
        renderer->Draw();
    }
}
