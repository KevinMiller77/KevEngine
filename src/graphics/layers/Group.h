#ifndef __KevEngine_GROUP__
#define __KevEngine_GROUP__

#include "../renderables/Renderable2D.h"

class Group : public Renderable2D
{
private:
    bool enabled = true;
    std::vector<Renderable2D*> children;
    Mat4f ModelMatrix;

public:
    Group() = default;
    Group(const Mat4f transform);
    ~Group()
    {
        for (Renderable2D* child : children)
        {
            delete child;
        }
    }

    void Add(Renderable2D* renderable);
    void Submit(KevRenderer* renderer) override;

    virtual void OnUpdate() override
    {
        for (Renderable2D* child : children)
        {
            child->OnUpdate();
        }
    }

    inline Texture* GetTextureFromChild(unsigned int index) const { return children[index]->GetTexturePtr(); }
    inline unsigned int GetNumChildren() { return children.size(); }

    //bool IsColliding(Renderable2D* other) override;
    virtual void CheckCollision(Renderable2D* other) override;
    virtual void MouseCheck(Vec2f& mousePos, std::vector<Renderable2D*>& underMouse) override;
    
    virtual inline void Delete(Renderable2D* Renderable)
    {
        for (int i = 0; i < children.size(); i++)
        {
            if (children[i] == Renderable)
            {
                children.erase(children.begin() + i);
            }
        }
    }
//        std::remove(children.begin(), children.end(), Renderable); }
    
    inline virtual void AddTransform(Mat4f Transform) { ModelMatrix = ModelMatrix * Transform; }

    inline virtual void* GetChildren() override { return (void*)&children; }

    inline virtual void Enable() { enabled = true; }
    inline virtual void Disable() { enabled = false; }
    inline virtual bool IsEnabled() { return enabled; }
};

#endif
