#ifndef __KevEngine_LAYER__
#define __KevEngine_LAYER__

#include "../BetterGL2DRenderer.h"
#include "../TextureManager.h"
#include "../FontManager.h"
#include "../ShaderManager.h"
#include "../../events/Event.h"
#include "../OrthographicCameraController.h"

class Layer
{
protected:
    Layer(GL2DRenderer *renderer, GLuint shader);

    GL2DRenderer *Renderer;
    std::vector<Renderable2D *> renderables;
    std::map<const char*, unsigned int> groupMap;
    GLuint Shader;

    TextureManager textures;
    FontManager fonts;

    bool enabled;

public:
    Layer() {};
    virtual ~Layer();

    virtual void add(Renderable2D *renderable);
    virtual void render();

    virtual inline GLuint getShader() { return Shader; }
    virtual inline void setShader(GLuint shader) { Shader = shader; }

    virtual void OnAttach() = 0;
    virtual void OnDetatch() = 0;

    virtual void OnUpdate() = 0;
    virtual void OnDraw() = 0;
    virtual void OnEvent(Event& e) = 0;

    virtual inline unsigned int getNumRenderables() { return renderables.size(); }

    virtual inline void pushTransform(Mat4f *transform) { Renderer->push(*transform); }
    virtual inline void poptransform() { Renderer->pop(); }

    inline void enable() { enabled = true; }
    inline void disable() { enabled = false; }
    inline void toggle() { enabled = !enabled; }
};

#endif