#include "Layer.h"

Layer::Layer(Window* Parent, KevRenderer *Renderer, unsigned int Shader, Kev2DCamera* Camera)
    : parent(Parent), renderer(Renderer), shader(Shader), enabled(true), camera(Camera)
{
    keyDebounce.Start();
}

Layer::~Layer()
{
    
#ifdef KEV_PLATFORM_MACOS
#else
    delete renderer;
#endif

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
//        ShaderProgram::Cre(shader);
        renderer->Begin();

        for (Renderable2D *renderable : renderables)
        {
            renderable->Submit(renderer);
        }
        
        renderer->End();   
        renderer->Draw();
    }
}
