#ifndef __KevEngine_LAYER__
#define __KevEngine_LAYER__

#include<utils/Timer.h>

#include <events/Event.h>

#include <graphics/KevRenderer.h>
#include <graphics/Window.h>

#include <graphics/cameras/Kev2DCamera.h>
#include <graphics/TextureManager.h>
#include <graphics/FontManager.h>
#include <graphics/RenderableManager.h>
#include <graphics/cameras/OrthographicCameraController.h>
#include <graphics/api/ShaderProgram.h>


class Layer
{
protected:
    Layer(Window* Parent, KevRenderer *Renderer, unsigned int Shader, Kev2DCamera* Camera);

    Window* parent;
    
    
    KevRenderer *renderer;
    std::vector<Renderable2D *> renderables;
    RenderableManager Manager = RenderableManager(&renderables);
    Kev2DCamera* camera;
    unsigned int shader;

    TextureManager textures;
    FontManager fonts;

    Timer keyDebounce;
    float keyDebounceInterval = 0.05f;

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
    
    virtual inline void SetCamera(Kev2DCamera* Camera) { if (Camera != nullptr) camera = Camera; }

    inline void Enable() { enabled = true; }
    inline void Disable() { enabled = false; }
    inline void Toggle() { enabled = !enabled; }
};

#endif
