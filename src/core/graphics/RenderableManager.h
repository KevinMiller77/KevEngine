#ifndef __RENDERABLE_MANAGER__
#define __RENDERABLE_MANAGER__

#include <vector>
#include <algorithm>
#include <map>
#include <core/math/math.h>
#include <core/events/Event.h>
#include "renderables/Renderable2D.h"
#include "layers/Group.h"

enum class Attributes
{
    RigidBody, Controlled
};

class RenderableManager
{
protected:
    std::vector<Renderable2D*>* ManagedRenderables;

public:
    RenderableManager(std::vector<Renderable2D*>* Renderables);

    void OnUpdate();
    void OnEvent(Event& e);

    void MouseCheck(Vec2f MousePos);
    void CollisionCheck();

    inline static bool SortRenderablesByScreenX(const void* p1, const void* p2) { return ((Renderable2D*)p1)->GetWorldLeftBound() <= ((Renderable2D*)p2)->GetWorldLeftBound(); } 
};

#endif