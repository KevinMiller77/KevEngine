#include "PhysicsSprite.h"
#include <core/KevInput.h>
#include <graphics/layers/Layer.h>

PhysicsSprite::PhysicsSprite(float x, float y, float width, float height, const Vec4f color)
    : Renderable2D(Vec3f(x, y, 0), Vec2f(width, height), color)
{
    centerOfMass = Vec3f(width / 2, height / 2, 0);
    Init();
}
PhysicsSprite::PhysicsSprite(float x, float y, float width, float height, GLTextureProgram* inTexture, bool GravityAffects)
    : Renderable2D(Vec3f(x, y, 0), Vec2f(width, height), inTexture)
{
    gravityAffects = GravityAffects;
    centerOfMass = Vec3f(width / 2, height / 2, 0);
    Init();
}

PhysicsSprite::PhysicsSprite(Renderable2D* newMe)
    : Renderable2D(newMe)
{
    float comX = newMe->GetSize().x / 2;
    float comY = newMe->GetSize().y / 2;
    centerOfMass = Vec3f(comX, comY, 0);
    Init();
}

void PhysicsSprite::Init()
{
    type = RenderableType::Physics;
    debounce.Start();
    movement.Start();
    color = 0xFFFF00FF;
    velocity = Vec3f(0.0f, 0.0f, 0.0f);
    screenPos = GetScreenPos();
    
    collisionMagnitude = vector<CollisionDirection>();
}

void PhysicsSprite::OnClick()
{
    if (debounce.GetTimePassed() > 0.5f)
    {
        activated = !activated;
        debounce.Reset();
    }
}

void PhysicsSprite::OnUpdate()
{

    double ts = movement.GetTimePassed();
    
    ProcCollision();
    correctColliderOverlap = Vec2f(0, 0);
    
    velocity.x += acceleration.x * ts;
    velocity.y += acceleration.y * ts;
    velocity.z += acceleration.z * ts;

    // LOG_INF("Vel to be added %f, %f, %f\n", velocity.x * ts, velocity.y * ts, velocity.z * ts);

    position.x += velocity.x * ts;
    position.y += velocity.y * ts;
    //Temporary
    position.z = 1;
    
    if (position.y < 0)
    {
        velocity.y = 0;
        position.y -= position.y;
    }
    else if (position.y + size.y > 18)
    {
        stable = true;
        velocity.y = 0;
        position.y -= (position.y + size.y - 18);
    }
    if (position.x < 0)
    {
        velocity.x = 0;
        position.x -= position.x;
    }
    else if (position.x + size.x > 32)
    {
        velocity.x = 0;
        position.x -= position.x + size.x - 32;
    }

    screenPos = GetScreenPos();

    if (stable)
    {
        velocity.x *= 0.95f;
    }
    
    movement.Reset();
    acceleration = Vec3f(0, 0, 0);
    nextMove = Vec3f(0, 0, 0);
}

const void PhysicsSprite::AddMomentum(Vec3f Momentum)
{
    acceleration.x += Momentum.x;
    acceleration.y += Momentum.y;
    acceleration.z += Momentum.z;
}

Vec4f GetOffset(Renderable2D* one, Renderable2D* two)
{
    Vec2f myPos = Vec2f(one->GetPosition().x, one->GetPosition().y);
    Vec2f myCenter = Vec2f(one->GetPosition().x + one->GetSize().x / 2, one->GetPosition().y + one->GetSize().y / 2);
    Vec2f otherPos = Vec2f(two->GetPosition().x, two->GetPosition().y);
    Vec2f otherSize = two->GetSize();
    Vec2f otherCenter = Vec2f(otherPos.x + otherSize.x / 2, otherPos.y + otherSize.y);//[0]    float    4.5
    
    Vec2f diff = myCenter - otherCenter;
    Vec2f shit = Vec2f(0, 0);
    shit.x = min(max(diff.x, -otherSize.x / 2.0f), otherSize.x / 2.0f);
    shit.y = min(max(diff.y, -otherSize.y / 2.0f), otherSize.y / 2.0f);
    Vec2f clampedOther = otherCenter + shit;
    
    Vec2f realDiff = (clampedOther - myCenter, diff);
    
    return Vec4f(-realDiff.x, -realDiff.y, diff.x, diff.y);
}

void PhysicsSprite::AddCollision(Renderable2D* collidedWith) //false = right/dn; true = left/up
{
    if (collidedWith == nullptr)
    {
        //Colliding without a collided doesn't make much sense for this guy
            //It does, however, make sense for the regular sprite. It doesn't calculate movement, it has none
        return;
    }
    
    hadCollision = true;
    
    //TODO: Find full overlap
    Vec4f diffs = GetOffset(this, collidedWith);
    Vec2f overlap = Vec2f(diffs.x, diffs.y);
    Vec2f diff = Vec2f(diffs.z, diffs.w);
    
    
    //TODO:
    Vec2f compass[] = {
        Vec2f(0.0f, 1.0f),    // up
        Vec2f(1.0f, 0.0f),    // right
        Vec2f(0.0f, -1.0f),    // down
        Vec2f(-1.0f, 0.0f)    // left
    };
    
    float bests[4];

    float max = 0.0f;
    unsigned int best_match = -1;
    for (unsigned int i = 0; i < 4; i++)
    {
        float dot_product = Vec2f::dot(overlap.normal(), compass[i]);
        bests[i] = dot_product;
        if (dot_product > max)
        {
            max = dot_product;
            best_match = i;
        }
    }
    
    // Decide which was the best match
    CollisionDirection direction = (CollisionDirection)best_match;

    if (direction == CollisionDirection::DOWN)
    {
        if (size.x - abs(diff.x) < size.y - abs(diff.y))
        {
            if (bests[1] > bests[3])
            {
                direction = CollisionDirection::RIGHT;
            }
            else
            {
                direction = CollisionDirection::LEFT;
            }
        }
    }
    
    collisionMagnitude.push_back(direction);
    
    if (direction == CollisionDirection::UP || direction == CollisionDirection::DOWN)
    {
        velocity.y = 0;
        if (direction == CollisionDirection::DOWN)
        {
//            LOG_INF("D\n");
            position.y -= size.y + diff.y;
        }
        else
        {
            position.y += size.y / 2 - diff.y;
        }
    }
    else
    {
        velocity.x = 0;
        if (direction == CollisionDirection::RIGHT)
        {
            position.x -= size.x + diff.x;
        }
        else
        {
            position.x += size.x - diff.x;
        }
    }
    
}

void PhysicsSprite::ProcCollision()
{
    if (!hadCollision)
    {
        stable = false;
        return;
    }
    
    stable = false;
    for (CollisionDirection col : collisionMagnitude)
    {
        if (col == CollisionDirection::DOWN)
        {
            stable = true;
        }
    }
    collisionMagnitude.clear();
    
    hadCollision = false;
}

void PhysicsSprite::NoCollision()
{

}
