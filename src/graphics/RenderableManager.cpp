#include "RenderableManager.h"

RenderableManager::RenderableManager(std::vector<Renderable2D*>* Renderables)
    : ManagedRenderables(Renderables)   
{
    
}

void RenderableManager::MouseCheck(Vec2f MousePos)
{
    // printf("Player Pos: %f, %f\t World Pos: %f, %f\n", player->getPosition().x, player->getPosition().y, player->GetScreenPos().x, player->GetScreenPos().y);
    std::vector<Renderable2D*> underMouse;
    for (int rend = ManagedRenderables->size() - 1; rend >= 0; rend--)
    {
        (*ManagedRenderables)[rend]->MouseCheck(MousePos, underMouse);
    }
}

void RenderableManager::CollisionCheck()
{
    std::vector<Renderable2D*> Renderables = *ManagedRenderables;
    std::vector<Renderable2D*> RenderablesToCheck;
    std::vector<Renderable2D*>::iterator pos = Renderables.begin();

    unsigned int sizeOfRenderables = Renderables.size(); 
    for (unsigned int i = 0; i < sizeOfRenderables; i++)
    {
        if (!Renderables[i]->IsSingleRenderable())
        {
            std::vector<Renderable2D*> curGroup = *(std::vector<Renderable2D*>*)(Renderables[i]->GetChildren());
            Renderables.insert(++pos, curGroup.begin(), curGroup.end());
            sizeOfRenderables = Renderables.size();
            continue;
        }

        if (Renderables[i]->GetType() != RenderableType::Physics)
        {
            pos++;
            continue;
        }

        RenderablesToCheck.push_back(Renderables[i]);
        pos++;
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
            //New renderable passed old
            if (RigidBody->GetWorldLeftBound() >= second->GetWorldRightBound())
            {
                continue;
            }

            //Collision already happened
            if (detectedCollisions[RigidBody] == second)
            {
                // LOG_INF("already happened\n");
                continue;
            }

            bool sideDir = false; // false is left, true is right

            if (RigidBody->GetWorldRightBound() > second->GetWorldRightBound())
            {
                sideDir = true;
            }
            
            // LOG_INF("Looking at %f %f, and %f %f\n", RigidBody->GetWorldLeftBound(), RigidBody->GetWorldUpBound(), second->GetWorldLeftBound(), second->GetWorldUpBound());
            //Collision
            if ((RigidBody->GetWorldUpBound() <= second->GetWorldUpBound() && RigidBody->GetWorldDownBound() >= second->GetWorldDownBound()))
            {
                detectedCollisions[RigidBody] = second; detectedCollisions[second] = RigidBody;
                
                // LOG_INF("Up collide\n");
                RigidBody->OnCollision(second, sideDir, true);
                if (second->GetType() == RenderableType::Physics)
                {
                    second->OnCollision(RigidBody, !sideDir, false);
                }
            }
            if (RigidBody->GetWorldUpBound() >= second->GetWorldUpBound() && RigidBody->GetWorldDownBound() <= second->GetWorldDownBound())
            {
                detectedCollisions[RigidBody] = second; detectedCollisions[second] = RigidBody;
                
                // LOG_INF("Down collide\n");
                RigidBody->OnCollision(second, sideDir, false);
                if (second->GetType() == RenderableType::Physics)
                {
                    second->OnCollision(RigidBody, !sideDir, true);
                }
            }
        
        }
        
        CurrentlyViewing.push_back(RigidBody);
    }
}