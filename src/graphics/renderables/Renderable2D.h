#ifndef __RENDERABLE_2D__
#define __RENDERABLE_2D__
#include "Entity2D.h"
#include "../buffers/IndexBuffer.h"
#include "../buffers/VertexArray.h"
#include "../../utils/Logging.h"
#include "../../utils/SOIL2/SOIL2.h"

struct VertexData
{
    Vec3f vertex;
    Vec4f color;
    Vec2f tex;
};

struct Texture
{
    const char *imagePath;
    int *width;
    int *height;
    int *nrChannels;

    GLuint *texture;
    float *verticies;
};

class Renderable2D : virtual public Entity2D
{
private:
    const char *ID;

protected:
    VertexArray *VAO;
    IndexBuffer *IBO;

    GLuint ShaderProgramID;
    GLuint *texID;

public:
    Texture *tex;
    Renderable2D() = default;
    Renderable2D(const char *in_ID, Vec3f pos, Vec2f size, Vec4f col, GLuint shaderProg);
    virtual ~Renderable2D();

    void LoadTexture(const char *inImagePath);

    inline const VertexArray *getVAO() const { return VAO; };
    inline const IndexBuffer *getIBO() const { return IBO; };

    inline const GLuint *getTexturePtr() const { return texID; }
    inline const GLuint getTextureID() const { return *texID; }

    inline const GLuint getShaderID() const { return ShaderProgramID; }
};

#endif