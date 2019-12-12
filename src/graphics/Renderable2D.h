#ifndef __RENDERABLE_2D__
#define __RENDERABLE_2D__
#include "Entity2D.h"
#include "buffers/IndexBuffer.h"
#include "buffers/VertexArray.h"

class Renderable2D : virtual public Entity2D
{
protected:
    VertexArray* VAO;
    IndexBuffer* IBO;

    GLuint ShaderProgramID;  

public:
    Renderable2D() = default;
    Renderable2D(const char* ID, Vec3 pos, Vec2 size, Vec4 col, GLuint shaderProg);
    virtual ~Renderable2D();

    inline const VertexArray* getVAO() const { return VAO; };
    inline const IndexBuffer* getIBO() const { return IBO; };
    
    inline const GLuint getShaderID() const { return ShaderProgramID; }

};

#endif