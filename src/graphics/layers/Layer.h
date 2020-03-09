#ifndef __TLETC_LAYER__
#define __TLETC_LAYER__

#include "../BetterGL2DRenderer.h"
#include "../TextureProgram.h"

class Layer
{
protected:
    Layer(GL2DRenderer *renderer, GLuint shader, Mat4f projMatrix);

    GL2DRenderer *Renderer;
    std::vector<Renderable2D *> renderables;
    std::map<const char*, unsigned int> groupMap;
    GLuint Shader;

    Mat4f projectionMatrix;
    bool enabled;

public:
    virtual ~Layer();

    virtual void add(Renderable2D *renderable);
    virtual void render();

    virtual inline GLuint getShader() { return Shader; }
    virtual inline void setShader(GLuint shader) { Shader = shader; }

    virtual inline unsigned int getNumRenderables() { return renderables.size(); }

    virtual inline void pushTransform(Mat4f *transform) { Renderer->push(*transform); }
    virtual inline void poptransform() { Renderer->pop(); }

    inline void enable() { enabled = true; }
    inline void disable() { enabled = false; }
    inline void toggle() { enabled = !enabled; }
};

#endif