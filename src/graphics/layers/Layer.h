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
    GLuint Shader;

    Mat4f projectionMatrix;

public:
    virtual ~Layer();
    Texture *texture;

    virtual void add(Renderable2D *renderable);
    virtual void render();

    virtual inline GLuint getShader() { return Shader; }
    virtual inline void setShader(GLuint shader) { Shader = shader; }
    
    virtual void genTexture(const char* path) { texture = new Texture(path); }
    virtual unsigned int getNumRenderables() {return renderables.size(); }
};

#endif