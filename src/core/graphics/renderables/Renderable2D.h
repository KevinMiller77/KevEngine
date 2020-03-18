#ifndef __RENDERABLE_2D__
#define __RENDERABLE_2D__

#include "../../math/math.h"
#include "../buffers/IndexBuffer.h"
#include "../buffers/VertexArray.h"

#include "../GL2DRenderer.h"
#include "../TextureProgram.h"

#include "../../utils/Logging.h"
#include "../ShaderProgram.h"

#include <core/events/Event.h>

enum CollisionDir
{
    CollisionUp, CollisionDown, CollisionLeft, CollisionRight
};

struct VertexData
{
    Vec3f vertex;
    Vec2f texture;
    float texID;
    uint32_t color;
};

class Renderable2D
{
protected:
    const char* name;
    Vec3f position;
    Vec2f size;
    uint32_t color = 0;

    Texture* texture;
    GLuint texID;

    Vec3f* baseOrigin = nullptr;

    bool SolidObject = true;

    Renderable2D() : texture(nullptr) { texID = 0; };
public:
    Renderable2D(Vec3f pos, Vec2f size, Vec4f col)
        : size(size)
    {
        position = pos;

        uint32_t c;
        uint32_t r = (int)(col.x * 255.0f);
        uint32_t g = (int)(col.y * 255.0f);
        uint32_t b = (int)(col.z * 255.0f);
        uint32_t a = (int)(col.w * 255.0f);
        
        c = a << 24 | b << 16 | g << 8 | r;

        color = c;

        texture = nullptr;
        texID = 0;
    }
    virtual ~Renderable2D() = default;

    virtual void submit(GL2DRenderer* renderer) const
    {
        renderer->submit(this);
    }

    inline virtual const Vec3f &getPosition() const { return position; }
    inline virtual const Vec2f &getSize() const { return size; }
    inline virtual const uint32_t &getColor() const { return color; }
    inline virtual const GLuint getTextureID() const { return texID; }
    inline virtual Texture* getTexturePtr() { return texture; }

    inline virtual const void setPosition(Vec3f &newPosition) { position = newPosition; }
    inline virtual const void setSize(Vec2f &newSize) { size = newSize; }
    inline virtual const void setColor(Vec4f newColor) 
    { 
        uint32_t c;
        uint32_t r = (int)(newColor.x * 255.0f);
        uint32_t g = (int)(newColor.y * 255.0f);
        uint32_t b = (int)(newColor.z * 255.0f);
        uint32_t a = (int)(newColor.w * 255.0f);
        
        c = a << 24 | b << 16 | g << 8 | r;
        color = c;
    }
    inline virtual const void setColor(uint32_t newColor) { color = newColor; }

    inline virtual const void SetBase(Vec3f* origin) { baseOrigin = origin; }

    inline float GetLeftBound() { return position.x; }
    inline float GetRightBound() { return position.x + size.x; }
    inline float GetUpBound() { return position.y; }
    inline float GetDownBound() {return position.y + size.y; }

    inline bool IsSolid()   {return SolidObject; }
    inline void SetSolid(bool isSolid)   {SolidObject = isSolid; }

    virtual void OnMouseHover() {}
    virtual void OnCollision(Renderable2D* collidedWith) {}
    virtual void OnClick() {}

    Vec3f GetWorldPos()
    {
        if (baseOrigin == nullptr) return Vec3f(0, 0, 0);

        return Vec3f(position.x + baseOrigin->x, position.y + baseOrigin->y, position.z + baseOrigin->z);
    }
};

#endif