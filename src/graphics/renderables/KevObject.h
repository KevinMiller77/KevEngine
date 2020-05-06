#ifndef __KEV_BASE_OBJECT__
#define __KEV_BASE_OBJECT__

#include <graphics/layers/Group.h>
#include <math/math.h>

enum class AttributeType
{
    RENDERABLE   = BIT(0),
    RIGID        = BIT(1),
    CONTROLLED   = BIT(2),
    LIGHT        = BIT(3),
    SOUND        = BIT(4)
};

class KevObject : public Group
{
    //This group will have the internal position
    Group* IntGroup = nullptr;
    
public:
    KevObject(Mat4f transform = Mat4f(1.0f)) : Group(transform)
    {
        Mat4f inMmat = transform.invertMatrix();
        IntGroup = new Group(inMmat);
        IntGroup->SetBase(baseOrigin);
        IntGroup->SetParent((Renderable2D*)this);
        children.push_back(IntGroup);
    }
    ~KevObject()
    {
        
    }
    
    inline virtual void Add(Renderable2D* renderable) override
    {
        IntGroup->Add(renderable);
    }
    inline virtual void Submit(KevRenderer* renderer) override
    {
        renderer->Push(ModelMatrix);
        IntGroup->Submit(renderer);
        renderer->Pop();
    }
    
    virtual void OnAdd(Renderable2D* renderable) {}
    virtual void OnSubmit() {}
    
    inline void Rotate(float angle, Vec3f axis) { AddTransform(Mat4f::rotation(angle, axis)); }
};


#endif
