#ifndef __STATIC_SPRITE_2D__
#define __STATIC_SPRITE_2D__

#include "Renderable2D.h"

class StaticSprite : public Renderable2D
{
private:
    VertexArray* VAO;
    IndexBuffer* IBO;
    ShaderProgram* shader;
 
public:
    StaticSprite(float x, float y, float width, float height, Vec4f color, ShaderProgram* inShader);
    ~StaticSprite() = default;
    
    inline const VertexArray *getVAO() const { return VAO; }
    inline const IndexBuffer *getIBO() const { return IBO; }

    inline ShaderProgram* getShader() const { return shader; }
};

#endif