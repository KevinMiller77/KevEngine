#ifndef __KevEngine_LAYER__
#define __KevEngine_LAYER__

#include "../GL2DRenderer.h"

#include "../TextureManager.h"
#include "../FontManager.h"
#include "../RenderableManager.h"

#include "../../events/Event.h"
#include "../cameras/OrthographicCameraController.h"

class Layer
{
protected:
    Layer(GL2DRenderer *renderer, unsigned int shader);

    GL2DRenderer *Renderer;
    std::vector<Renderable2D *> renderables;
    RenderableManager Manager = RenderableManager(&renderables);
    unsigned int Shader;

    TextureManager textures;
    FontManager fonts;

    bool enabled;

public:
    Layer() {};
    virtual ~Layer();

    virtual void Add(Renderable2D *renderable);
    virtual void Render();

    virtual inline unsigned int GetShader() { return Shader; }
    virtual inline void SetShader(unsigned int shader) { Shader = shader; }

    virtual void OnAttach() {};
    virtual void OnDetach() {};

    virtual void OnUpdate() {};
    virtual void OnDraw() {};
    virtual void OnImGuiRender() {}
    virtual void OnEvent(Event& e) {};

    virtual inline unsigned int GetNumRenderables() { return renderables.size(); }

    virtual inline void PushTransform(Mat4f *transform) { Renderer->Push(*transform); }
    virtual inline void PopTransform() { Renderer->Pop(); }

    inline void Enable() { enabled = true; }
    inline void Disable() { enabled = false; }
    inline void Toggle() { enabled = !enabled; }
};

#endif