#ifndef __RENDERABLE_2D__
#define __RENDERABLE_2D__
#include "../../math/math.h"
#include "../buffers/IndexBuffer.h"
#include "../buffers/VertexArray.h"
#include "../../utils/Logging.h"
#include "../ShaderProgram.h"

struct VertexData
{
    Vec3f vertex;
    Vec4f color;
    Vec2f texture;
};

class Renderable2D
{
protected:
    Vec3f position;
    Vec2f size;
    Vec4f color;

public:
    Renderable2D(Vec3f pos, Vec2f size, Vec4f col)
        : position(pos), size(size), color(col)
    {
    }
    virtual ~Renderable2D() {}

    inline virtual const Vec3f &getPosition() const { return position; }
    inline virtual const Vec2f &getSize() const { return size; }
    inline virtual const Vec4f &getColor() const { return color; }

    inline virtual const void setPosition(Vec3f &newPosition) { position = newPosition; }
    inline virtual const void setSize(Vec2f &newSize) { size = newSize; }
    inline virtual const void setColor(Vec4f newColor) { color = newColor; }
};

#endif