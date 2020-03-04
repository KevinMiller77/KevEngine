#ifndef __TLETC_LAYER__
#define __TLETC_LAYER__

#include "../BetterGL2DRenderer.h"
#include "../TextureProgram.h"

class Layer
{
protected:
    Layer(GL2DRenderer *renderer, ShaderProgram *shader, Mat4f projMatrix);
    ~Layer();

    GL2DRenderer *Renderer;
    std::vector<Renderable2D *> renderables;
    ShaderProgram *Shader;

    Mat4f projectionMatrix;

public:
    Texture *texture;

    virtual void add(Renderable2D *renderable);
    virtual void render();
    virtual inline ShaderProgram *getShader() { return Shader; }
};

#endif