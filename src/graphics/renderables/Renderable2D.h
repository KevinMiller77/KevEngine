#ifndef __RENDERABLE_2D__
#define __RENDERABLE_2D__

#include <string>
#include <math/math.h>
#include <graphics/buffers/IndexBuffer.h>
#include <graphics/buffers/VertexArray.h>
#include <graphics/renderer/TextureProgram.h>
#include <utils/Logging.h>
#include <graphics/renderer/ShaderProgram.h>
//Has to be included last
#include <graphics/renderer/GL2DRenderer.h>
#include <core/KevInput.h>

enum class RenderableType
{
    None = 0,
    Static,
    Physics,
    Terrain,
    Group
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
    unsigned int uid = 0;
    
    Vec3f position;
    Vec3f screenPos;
    Vec2f size;
    uint32_t color = 0;

    Texture* texture;
    unsigned int texID;

    Vec3f* baseOrigin = nullptr;

    bool SolidObject = false;
    bool mouseHovering = false;
    bool singleItem = true;

    RenderableType type = RenderableType::None;

    Renderable2D() : texture(nullptr) { texID = 0; };
public:
    Renderable2D(Vec3f Position, Vec2f Size, Vec4f Color, const char* Name = ("REND_" + std::to_string(GetGlobalNumRenderables())).c_str())
        : size(Size), uid(globalNumRenderables)
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
    
    Renderable2D(Vec3f Position, Vec2f Size, Texture* inTexture, const char* Name = ("REND_" + std::to_string(GetGlobalNumRenderables())).c_str())
        : size(Size), uid(globalNumRenderables)
    {
        position = Position;
        color = 0xFFFFFFFF;
        texture = inTexture;
        texID = inTexture->GetTexID();
        globalNumRenderables++;
    }

    Renderable2D(Renderable2D* newMe)
    {
        if (newMe->GetType() == RenderableType::Group)
        {
            singleItem = false;
            LOG_ERR("Tried to convert a group type!!\n");
        }
        type = newMe->GetType();
        position = newMe->GetPosition();
        color = newMe->GetColor();
        screenPos = newMe->GetScreenPos();
        texture = newMe->GetTexturePtr();
        texID = newMe->GetTextureID();
        name = newMe->GetName();
    }

    virtual ~Renderable2D() = default;

    inline virtual void Submit(GL2DRenderer* renderer) const { renderer->Submit(this); }

    inline virtual const Vec3f &GetPosition() const { return position; }
    inline virtual const void SetPosition(Vec3f* newPosition) { position = *newPosition; }

    inline virtual const void AddMomentum(Vec3f Momentum) {}; 
    
    inline virtual const Vec2f &GetSize() const { return size; }
    inline virtual const void SetSize(Vec2f &newSize) { size = newSize; }
    
    inline virtual const uint32_t &GetColor() const { return color; }
    inline virtual const void SetColor(Vec4f newColor) {color = newColor.ColorAsInt(); }
    inline virtual const void SetColor(uint32_t newColor) { color = newColor; }
    
    inline virtual Texture* GetTexturePtr() { return texture; }
    
    inline virtual const char* GetName()    { return name; }
    inline virtual const void SetName(const char* Name) { name = Name; }
    
    inline virtual const unsigned int GetUID() { return uid; }
    inline virtual const unsigned int GetTextureID() const { return texID; }

    inline virtual const void SetBase(Vec3f* origin) { baseOrigin = origin; screenPos = GetScreenPos(); }
    inline virtual const Vec3f* GetBase() { return baseOrigin; }

    inline float GetLeftBound() { return position.x; }
    inline float GetRightBound() { return position.x + size.x; }
    inline float GetUpBound() { return position.y; }
    inline float GetDownBound() {return position.y + size.y; }

    inline float GetWorldLeftBound() {  screenPos = GetScreenPos(); return screenPos.x; }
    inline float GetWorldRightBound() { screenPos = GetScreenPos(); return screenPos.x + size.x; }
    inline float GetWorldUpBound() {    screenPos = GetScreenPos(); return screenPos.y; }
    inline float GetWorldDownBound() {  screenPos = GetScreenPos(); return screenPos.y + size.y; }

    Vec3f GetWorldCornerPos(bool x, bool y, bool z = 0) //false = left/dn/far; true = right/up/close
    {
        float xOut, yOut, zOut;

        xOut = x ? GetWorldRightBound() : GetWorldLeftBound();
        yOut = y ? GetWorldUpBound() : GetWorldDownBound();
        //TODO: Add 3d object support
        z = 0;


        return Vec3f(xOut, yOut, zOut);
    }


    inline bool IsSolid()   {return SolidObject; }
    inline void SetSolid(bool isSolid)   {SolidObject = isSolid; }

    inline bool IsSingleRenderable() { return singleItem; }
    inline virtual void* GetChildren() { return (void*)this; }

    inline RenderableType GetType() { return type; }
    inline void SetType(RenderableType newType) { type = newType; }

    virtual void CheckCollision(Renderable2D* other)
    {
    }

    //Checks if the mouse is hovering over any renderables, if so it will return a vector of them
    virtual void MouseCheck(Vec2f& mousePos, std::vector<Renderable2D*>& underMouse) 
    {
        if ((mousePos.x > GetScreenPos().x && mousePos.x < GetScreenPos().x + size.x) && (mousePos.y > GetScreenPos().y && mousePos.y < GetScreenPos().y + size.y))
        {
            if (underMouse.size() == 0)
            {
                OnMouseHover();
                if (KevInput::IsMouseButtonPressed(KEV_MOUSE_BUTTON_LEFT))
                    {
                        OnClick();
                    }
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

    inline virtual void OnUpdate() {}

    inline virtual void OnMouseHover() {}
    inline virtual void OnMouseLeave() {}
    inline virtual void OnCollision(Renderable2D* collidedWith, bool SideDir, bool VertDir) {}
    inline virtual void NoCollision() {}
    inline virtual void OnClick() {}

    Vec3f GetScreenPos()
    {
        if (baseOrigin == nullptr) return Vec3f(position.x, -position.y, 0);
        return Vec3f(position.x + baseOrigin->x, position.y + baseOrigin->y, position.z + baseOrigin->z);
    }

    inline static void GameStart() { globalNumRenderables = 0; }
    inline static unsigned int GetGlobalNumRenderables()    { return globalNumRenderables; } 
};

#endif
