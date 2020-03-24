#include "Layer.h"
#include <graphics/renderables/Sprite2D.h>

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
        ShaderProgram::EnableShaderProgram(shader);
        renderer->Begin();

        for (Renderable2D *renderable : renderables)
        {
            renderable->Submit(renderer);
        }
        
        renderer->End();   
        unsigned int tex = renderer->DrawToBuffer();


        Renderable2D* spr = new Sprite(-parent->GetWidth() / 2, parent->GetHeight() / 2, parent->GetWidth() / 2, parent->GetHeight(), tex);

        renderer->Begin();
        spr->Submit(renderer);
        renderer->End();  

        renderer->Draw();
    }
}
