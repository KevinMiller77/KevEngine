#ifndef __STATIC_SPRITE_2D__
#define __STATIC_SPRITE_2D__

#include "Renderable2D.h"

class StaticSprite : public Renderable2D
{
private:
    Vec3f pos;
    Vec2f size;

public:
    StaticSprite(char *ID, GLuint shaderProg, float x, float y, float width, float height, Vec4f color, char *texLocation);

    inline const Vec3f getPos() { return pos; }
    inline const Vec2f getSize() { return size; }
};

#endif