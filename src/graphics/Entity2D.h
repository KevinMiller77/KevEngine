#ifndef __ENTITY_2D__
#define __ENTITY_2D__

#include <GL/glew.h>
#include "../math/math.h"

class Entity2D
{
protected:
    const char* UniqueID;
    Vec3 Position;
    Vec2 Size;
    Vec4 Color;   

public:
    Entity2D() = default;
    Entity2D(const char* ID, Vec3 pos, Vec2 size, Vec4 col);
    virtual ~Entity2D();
    
    inline const char* getID()    const { return UniqueID; }
    inline const Vec3 getPosition() const { return Position; }
    inline const Vec2 getSize()     const { return Size; }
    inline const Vec4 getColor()    const { return Color; };

    
    inline const void setPosition(Vec3 newPosition) { Position = newPosition; }
    inline const void setSize(Vec2 newSize)         { Size = newSize; }
    inline const void setColor(Vec4 newColor)       { Color = newColor; };
};

#endif