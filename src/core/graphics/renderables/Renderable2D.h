#ifndef __RENDERABLE_2D__
#define __RENDERABLE_2D__

#include <string>
#include <core/Input.h> 
#include "../../math/math.h"
#include "../buffers/IndexBuffer.h"
#include "../buffers/VertexArray.h"

#include "../GL2DRenderer.h"
#include "../TextureProgram.h"

#include "../../utils/Logging.h"
#include "../ShaderProgram.h"

#include <core/events/Event.h>

enum RenderableType
{
    PlayerType,
    TerrainType,
    GroupType
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
    static unsigned int globalNumRenderables;
    const char* name = nullptr;
    
    Vec3f position;
    Vec2f size;
    uint32_t color = 0;

    Texture* texture;
    GLuint texID;

    Vec3f* baseOrigin = nullptr;

    bool SolidObject = true;
    bool mouseHovering = false;

    RenderableType type = TerrainType;

    Renderable2D() : texture(nullptr) { texID = 0; };
public:
    Renderable2D(Vec3f Position, Vec2f Size, Vec4f Color, const char* Name = ("REND_" + std::to_string(GetGlobalNumRenderables())).c_str())
        : size(Size)
    {
        position = Position;

        uint32_t c;
        uint32_t r = (int)(Color.x * 255.0f);
        uint32_t g = (int)(Color.y * 255.0f);
        uint32_t b = (int)(Color.z * 255.0f);
        uint32_t a = (int)(Color.w * 255.0f);
        
        c = a << 24 | b << 16 | g << 8 | r;

        color = c;

        texture = nullptr;
        texID = 0;

        globalNumRenderables++;
    }
    virtual ~Renderable2D() = default;

    inline virtual void submit(GL2DRenderer* renderer) const { renderer->submit(this); }

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
    inline virtual const Vec3f* GetBase() { return baseOrigin; }

    inline float GetLeftBound() { return position.x; }
    inline float GetRightBound() { return position.x + size.x; }
    inline float GetUpBound() { return position.y; }
    inline float GetDownBound() {return position.y + size.y; }

    inline bool IsSolid()   {return SolidObject; }
    inline void SetSolid(bool isSolid)   {SolidObject = isSolid; }

    inline RenderableType GetType() { return type; }
    inline void SetType(RenderableType newType) { type = newType; }

    virtual bool IsColliding(Renderable2D* other)
    {
        float topY1 = GetScreenPos().y;
        float bottomY1 = GetScreenPos().y + size.y;
        float topY2 = other->GetScreenPos().y;
        float bottomY2 = other->GetScreenPos().y + size.y;

        if ((topY1 < bottomY2 && bottomY1 > topY2) || (topY2 < bottomY1 && bottomY2 > topY1))
        {
            other->OnCollision(this);
            OnCollision(other);
            return true;
        } 
        return false;
    }

    //Checks if the mouse is hovering over any renderables, if so it will return a vector of them
    virtual void MouseCheck(Vec2f& mousePos, std::vector<Renderable2D*>& underMouse)
    {
        if ((mousePos.x > GetScreenPos().x && mousePos.x < GetScreenPos().x + size.x) && (mousePos.y > GetScreenPos().y && mousePos.y < GetScreenPos().y + size.y))
        {
            if (underMouse.size() == 0)
            {
                OnMouseHover();
                mouseHovering = true;
            } else if (mouseHovering)
            {
                OnMouseLeave();
                mouseHovering = false;
            }

            underMouse.push_back(this);
        }
        else if (mouseHovering)
        {
            OnMouseLeave();
            mouseHovering = false;
        }

    }

    virtual void OnMouseHover() {}
    virtual void OnMouseLeave() {}
    virtual void OnCollision(Renderable2D* collidedWith) {}
    virtual void NoCollision() {}
    virtual void OnClick() {}

    Vec3f GetScreenPos()
    {
        if (baseOrigin == nullptr) return Vec3f(position.x, -position.y, 0);
        return Vec3f(position.x + baseOrigin->x, position.y + baseOrigin->y, position.z + baseOrigin->z);
    }

    inline static void GameStart() { globalNumRenderables = 0; }
    inline static unsigned int GetGlobalNumRenderables()    { return globalNumRenderables; } 
};

#endif