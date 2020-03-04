#ifndef __TLETC_GROUP__
#define __TLETC_GROUP__

#include "../renderables/Renderable2D.h"

class Group : public Renderable2D
{
private:
    std::vector<Renderable2D*> children;
    Mat4f TransformationMatrix;

public:
    Group() = default;
    Group(const Mat4f transform);
    void add(Renderable2D* renderable);
    void submit(GL2DRenderer* renderer) const override;

};

#endif
