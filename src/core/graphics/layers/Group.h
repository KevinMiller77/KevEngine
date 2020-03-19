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

    void add(Renderable2D* renderable);
    void submit(GL2DRenderer* renderer) const override;

    inline Texture* getTextureFromChild(GLuint index) const { return children[index]->getTexturePtr(); }
    inline unsigned int getNumChildren() { return children.size(); }

    //bool IsColliding(Renderable2D* other) override;
    virtual void CheckCollision(Renderable2D* other) override;
    virtual void MouseCheck(Vec2f& mousePos, std::vector<Renderable2D*>& underMouse) override;

    inline virtual void* GetChildren() override { return (void*)&children; }
};

#endif
