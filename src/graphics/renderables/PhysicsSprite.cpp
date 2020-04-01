#include "PhysicsSprite.h"
#include <core/KevInput.h>

PhysicsSprite::PhysicsSprite(float x, float y, float width, float height, const Vec4f color)
    : Renderable2D(Vec3f(x, y, 0), Vec2f(width, height), color)
{
    centerOfMass = Vec3f(width / 2, height / 2, 0);
    Init();
}
PhysicsSprite::PhysicsSprite(float x, float y, float width, float height, Texture* inTexture, bool GravityAffects)
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

    float curMagV = sqrt(position.x * position.x + position.y * position.y);
    float nextMagV = sqrt(nextMove.x * nextMove.x + nextMove.y * nextMove.y);
    nextMagV = nextMagV == 0.0f ? 1.0f : nextMagV;
    float dot = velocity.x * (nextMove.x / nextMagV) + velocity.y * (nextMove.y / nextMagV);

    velocity.x += 0.8f * (-2.0f * dot * (nextMove.x / nextMagV));
    velocity.x += acceleration.x * ts;
    velocity.y += 0.8f * (-2.0f * dot * (nextMove.y / nextMagV));
    velocity.y += acceleration.y * ts;
    velocity.z += acceleration.z * ts;

    // LOG_INF("Vel to be added %f, %f, %f\n", velocity.x * ts, velocity.y * ts, velocity.z * ts);

    position.x += velocity.x * ts;
    position.y += velocity.y * ts;
    position.z += nextMove.z * ts;

    screenPos = GetScreenPos();

    movement.Reset();
    acceleration = Vec3f(0, 0, 0);
    nextMove = Vec3f(0, 0, 0);

    hadCollision = false;
}

const void PhysicsSprite::AddMomentum(Vec3f Momentum)
{
    double ts = movement.GetTimePassed();
    acceleration.x += Momentum.x * ts;
    acceleration.y += Momentum.y * ts;
    acceleration.z += Momentum.z * ts;
}

void PhysicsSprite::OnCollision(Renderable2D* collidedWith, bool SideDir, bool VertDir) //false = left/dn; true = right/up
{   
    double ts = movement.GetTimePassed();
    hadCollision = true;

    Vec3f overlap = collidedWith->GetWorldCornerPos(!SideDir, !VertDir) - GetWorldCornerPos(SideDir, VertDir);
    float magnitudeOfOverlap = sqrt(overlap.x * overlap.x + overlap.y * overlap.y);

    Vec3f comOther = Vec3f(collidedWith->GetSize().x / 2, collidedWith->GetSize().y / 2, 0.0f);
    Vec3f Moment = Vec3f(comOther.x - centerOfMass.x, comOther.y - centerOfMass.y, 0);

    nextMove.x += overlap.x  * (magnitudeOfOverlap * ts);
    nextMove.y += overlap.y  * (magnitudeOfOverlap * ts);
    nextMove.z += overlap.z  * (magnitudeOfOverlap * ts);

}

void PhysicsSprite::NoCollision()
{

}
