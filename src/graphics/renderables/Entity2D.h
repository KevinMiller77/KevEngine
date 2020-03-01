#ifndef __ENTITY_2D__
#define __ENTITY_2D__

#include <GL/glew.h>
#include "../../math/math.h"

class Entity2D
{
protected:
    const char *UniqueID;
    Vec3f Position;
    Vec2f Size;
    Vec4f Color;

public:
    Entity2D() = default;
    Entity2D(const char *ID, Vec3f pos, Vec2f size, Vec4f col);
    virtual ~Entity2D();

    inline const char *getID() const { return UniqueID; }
    inline const Vec3f getPosition() const { return Position; }
    inline const Vec2f getSize() const { return Size; }
    inline const Vec4f getColor() const { return Color; };

    inline const void setPosition(Vec3f newPosition) { Position = newPosition; }
    inline const void setSize(Vec2f newSize) { Size = newSize; }
    inline const void setColor(Vec4f newColor) { Color = newColor; };
};

#endif