#include "FollowRenderableCamera.h"

FollowRenderableCamera::FollowRenderableCamera(float horizontalMax, float verticalMax)
    : Camera(-horizontalMax, horizontalMax, -verticalMax, verticalMax)
{
    time.reset();
}

FollowRenderableCamera::FollowRenderableCamera(float horizontalMax, float verticalMax, Renderable2D* renderable)
    : Camera(-horizontalMax, horizontalMax, -verticalMax, verticalMax), renderableToFollow(renderable)
{
    time.reset();
}
    
void FollowRenderableCamera::OnUpdate()
{
    if (renderableToFollow == nullptr)
    {
        return;
    }
    
	double ts = time.getTimePassed();
    Vec3f renPos = renderableToFollow->GetScreenPos();
    Vec3f camPos = Camera.GetPosition();
    
    LOG_INF("Player Pos: %f, %f\t Cam Pos: %f, %f\n", renPos.x, renPos.y, camPos.x, camPos.y);

    float difX = renPos.x - camPos.x;
    float difY = renPos.y - camPos.y;

    
    Camera.SetPosition(Vec3f(-renPos.x, renPos.y, renPos.z)); 

    // if (abs(difX) > 0.25f)
    // {
    //     Camera.SetPosition(Vec3f(renPos.x, renPos.y, renPos.z)); 
    // }

    // if (abs(difY) > 0.25f)
    // {
    //     Camera.SetPosition(Vec3f(renPos.x, renPos.y, renPos.z)); 
    // }

    time.reset();
}

void FollowRenderableCamera::OnEvent(Event& e)
{

}