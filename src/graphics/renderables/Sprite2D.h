#ifndef __SPRITE_2D__
#define __SPRITE_2D__

#include "Renderable2D.h"

class Sprite : public Renderable2D
{
private:
public:
    Sprite(float x, float y, float width, float height, const Vec4f color);
    Sprite(float x, float y, float width, float height, Texture* inTexture);

};

#endif