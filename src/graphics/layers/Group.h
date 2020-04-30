#ifndef __KevEngine_GROUP__
#define __KevEngine_GROUP__

#include "../renderables/Renderable2D.h"

class Group : public Renderable2D
{
private:
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
    void Submit(KevRenderer* renderer) const override;

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

    inline virtual void* GetChildren() override { return (void*)&children; }
};

#endif
