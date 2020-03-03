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
};

class Renderable2D
{
protected:
    Vec3f position;
    Vec2f size;
    Vec4f color;

public:
    Renderable2D(Vec3f pos, Vec2f size, Vec4f col)
        :position(pos), size(size), color(color)
        { }
    virtual ~Renderable2D() { }
 
    inline const Vec3f& getPosition() const { return position; }
	inline const Vec2f& getSize() const { return size; }
	inline const Vec4f& getColor() const { return color; }

    inline const void setPosition(Vec3f& newPosition) { position = newPosition; }
	inline const void setSize(Vec2f& newSize) { size = newSize; }
	inline const void setColor(Vec4f newColor) { color = newColor; }

};

#endif