#ifndef __KevEngine_LAYER__
#define __KevEngine_LAYER__

#include<utils/Timer.h>

#include <events/Event.h>

#include <graphics/renderer/KevRenderer.h>
#include <graphics/Window.h>

#include <graphics/TextureManager.h>
#include <graphics/FontManager.h>
#include <graphics/RenderableManager.h>
#include <graphics/cameras/OrthographicCameraController.h>


class Layer
{
protected:
    Layer(Window* Parent, KevRenderer *Renderer, unsigned int Shader);

    Window* parent;
    
    
    KevRenderer *renderer;
    std::vector<Renderable2D *> renderables;
    RenderableManager Manager = RenderableManager(&renderables);
    unsigned int shader;

    TextureManager textures;
    FontManager fonts;

    Timer keyDebounce;
    float keyDebounceInterval = 0.2f;

    bool enabled;

public:
    Layer() {};
    virtual ~Layer();

    virtual void Add(Renderable2D *renderable);
    virtual void Render();

    virtual inline unsigned int GetShader() { return shader; }
    virtual inline void SetShader(unsigned int Shader) { shader = Shader; }

    virtual void OnAttach() {};
    virtual void OnDetach() {};

    virtual void OnUpdate() {};
    virtual void OnDraw() {};
    virtual void OnImGuiRender() {}
    virtual void OnEvent(Event& e) {};

    virtual inline unsigned int GetNumRenderables() { return renderables.size(); }

    virtual inline void PushTransform(Mat4f *transform) { renderer->Push(*transform); }
    virtual inline void PopTransform() { renderer->Pop(); }

    inline void Enable() { enabled = true; }
    inline void Disable() { enabled = false; }
    inline void Toggle() { enabled = !enabled; }
};

#endif
