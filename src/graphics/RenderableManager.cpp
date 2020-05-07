#include "RenderableManager.h"


RenderableManager::RenderableManager(std::vector<Renderable2D*>* Renderables)
    : ManagedRenderables(Renderables)   
{
    
}

void RenderableManager::MouseCheck(Vec2f MousePos, Vec2f CamOffset)
{
    // printf("Player Pos: %f, %f\t World Pos: %f, %f\n", player->getPosition().x, player->getPosition().y, player->GetScreenPos().x, player->GetScreenPos().y);
    std::vector<Renderable2D*> underMouse;
    for (int rend = ManagedRenderables->size() - 1; rend >= 0; rend--)
    {
        (*ManagedRenderables)[rend]->MouseCheck(MousePos + CamOffset, underMouse);
    }
}

void RenderableManager::CollisionCheck()
{
    std::vector<Renderable2D*> Renderables = *ManagedRenderables;
    std::vector<Renderable2D*> RenderablesToCheck;

    unsigned int sizeOfRenderables = Renderables.size(); 
    for (unsigned int i = 0; i < sizeOfRenderables; i++)
    {
        if (!Renderables[i]->IsSingleRenderable())
        {
            std::vector<Renderable2D*> curGroup = *(std::vector<Renderable2D*>*)(Renderables[i]->GetChildren());
            Renderables.insert(Renderables.begin() + i + 1, curGroup.begin(), curGroup.end());
            sizeOfRenderables = Renderables.size();
            continue;
        }

        if (Renderables[i]->GetType() == RenderableType::Group)
        {
            continue;
        }
        
        if (Renderables[i]->GetType() != RenderableType::Physics)
        {
            continue;
        }

        RenderablesToCheck.push_back(Renderables[i]);
    }


    std::sort(RenderablesToCheck.begin(), RenderablesToCheck.end(), RenderableManager::SortRenderablesByScreenX);
    // LOG_INF("Checking %d collisions\n", RenderablesToCheck.size());
    
    std::unordered_map <Renderable2D*, Renderable2D*> detectedCollisions;
    std::vector<Renderable2D*> CurrentlyViewing;
    for (Renderable2D* RigidBody : RenderablesToCheck)
    {
        RigidBody->NoCollision();
        // LOG_INF("\n%d was solid and possibly collides\n", RigidBody->GetUID());
        for (Renderable2D* second : CurrentlyViewing)
        {
            if (RigidBody == second)
            {
                continue;
            }
            
            //New renderable passed old
            if ((RigidBody->GetWorldLeftBound() > second->GetWorldRightBound()))
            {
                continue;
            }

            //Collision already happened
            if (detectedCollisions[RigidBody] == second)
            {
                // LOG_INF("already happened\n");
                continue;
            }
            
            //Collision
            if ((RigidBody->GetWorldUpBound() > second->GetWorldUpBound() && RigidBody->GetWorldUpBound() < second->GetWorldDownBound()))
            {
                detectedCollisions[RigidBody] = second; detectedCollisions[second] = RigidBody;
                SendCollision(RigidBody, second);
            }
            if (RigidBody->GetWorldDownBound() > second->GetWorldUpBound() && RigidBody->GetWorldDownBound() < second->GetWorldDownBound())
            {
                detectedCollisions[RigidBody] = second; detectedCollisions[second] = RigidBody;
                SendCollision(RigidBody, second);
            }
            if ((second->GetWorldUpBound() > RigidBody->GetWorldUpBound() && second->GetWorldUpBound() < RigidBody->GetWorldDownBound()))
            {
                detectedCollisions[second] = RigidBody; detectedCollisions[RigidBody] = second;
                SendCollision(second, RigidBody);
            }
            if (second->GetWorldDownBound() > RigidBody->GetWorldUpBound() && second->GetWorldDownBound() < RigidBody->GetWorldDownBound())
            {
                detectedCollisions[second] = RigidBody; detectedCollisions[RigidBody] = second;
                SendCollision(second, RigidBody);
            }
        
        }
        
        CurrentlyViewing.push_back(RigidBody);
    }
}

void RenderableManager::SendCollision(Renderable2D* Renderable)
{
    Renderable->AddCollision((Renderable2D*)nullptr);
}

void RenderableManager::SendCollision(Renderable2D* Renderable, Renderable2D* Affected)
{
    Renderable->AddCollision(Affected);
    
    if (Affected->GetType() == RenderableType::Physics)
    {
        Affected->AddCollision(Renderable);
    }
}
