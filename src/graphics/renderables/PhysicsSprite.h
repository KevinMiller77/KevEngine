#ifndef __PHYSICS_SPRITE__
#define __PHYSICS_SPRITE__

#include "Renderable2D.h"
#include <utils/Timer.h>

#include <math.h>

#define GRAVITY_CONSTANT 10.0f

class PhysicsSprite : public  Renderable2D
{
private:
    void Init();

    bool activated = false;
    Timer debounce;
    Timer movement; 
    
    double mass = 1.0f;
    bool gravityAffects = false;
    Vec3f acceleration = Vec3f(0, 0, 0);
    Vec3f velocity = Vec3f(0, 0, 0); 
    //Needs to be set in constructor because we don't yet know
    //the die lengths
    Vec3f centerOfMass;
    //A vector to build up collision events and then apply
    //during updates
    Vec3f nextMove = Vec3f(0, 0, 0);

    
    //Collision information
    vector<CollisionDirection> collisionMagnitude;
    float collisionAngle = 0.0f;
    bool hadCollision = false;
    Vec2f correctColliderOverlap;
    
    bool peggedX = false; //In between a solid object
    bool peggedY = false;
    

public:

    PhysicsSprite(float x, float y, float width, float height, const Vec4f color);
    PhysicsSprite(float x, float y, float width, float height, GLTextureProgram* inTexture, bool GravityAffects = false);
    PhysicsSprite(Renderable2D* newMe);

    virtual const void AddMomentum(Vec3f Momentum) override;

    virtual void OnUpdate() override;
    
    virtual void AddCollision(Renderable2D* collidedWith) override;
    virtual void ProcCollision() override;
    virtual void NoCollision() override;
    virtual void OnClick() override;

    inline void EnableGrav() { gravityAffects = true; }
    inline void DisableGrav() { gravityAffects = false; }

};


#endif
