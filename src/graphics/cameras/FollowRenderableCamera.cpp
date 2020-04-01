#include "FollowRenderableCamera.h"

FollowRenderableCamera::FollowRenderableCamera(float horizontalMax, float verticalMax)
    : Camera(-horizontalMax, horizontalMax, -verticalMax, verticalMax)
{
    time.Reset();
}

FollowRenderableCamera::FollowRenderableCamera(float horizontalMax, float verticalMax, Renderable2D* renderable)
    : Camera(-horizontalMax, horizontalMax, -verticalMax, verticalMax), renderableToFollow(renderable)
{
    time.Reset();
}
    
void FollowRenderableCamera::OnUpdate()
{
    if (renderableToFollow == nullptr)
    {
        return;
    }
    
	double ts = time.GetTimePassed();
    Vec3f renPos = renderableToFollow->GetScreenPos();
    Vec3f camPos = Camera.GetPosition();
    
    // LOG_INF("Player Pos: %f, %f\t Cam Pos: %f, %f\n", renPos.x, renPos.y, camPos.x, camPos.y);

    float newX = (renPos.x / (Camera.GetWidth() / 2)) - 1;
    float newY = (renPos.y / (Camera.GetHeight() / 2)) - 1;

    
    // Camera.SetPosition(new Vec3f(newX, newY, renPos.z)); 

    // if (abs(difX) > 0.25f)
    // {
    //     Camera.SetPosition(Vec3f(renPos.x, renPos.y, renPos.z)); 
    // }

    // if (abs(difY) > 0.25f)
    // {
    //     Camera.SetPosition(Vec3f(renPos.x, renPos.y, renPos.z)); 
    // }

    time.Reset();
}

bool FollowRenderableCamera::func (KeyPressedEvent& e)
{
    // if (e.GetKeyCode() == (int)KEV_KEY_D)
    //     Camera.SetPosition(new Vec3f(Camera.GetPosition().x + 0.5f, Camera.GetPosition().y, Camera.GetPosition().z));

    // if (e.GetKeyCode() == (int)KEV_KEY_A)
    //     Camera.SetPosition(new Vec3f(Camera.GetPosition().x - 0.5f, Camera.GetPosition().y, Camera.GetPosition().z));

    return false;
}

void FollowRenderableCamera::OnEvent(Event& e)
{

    EventDispatcher dispatch(e);
    dispatch.Dispatch<KeyPressedEvent>(KEV_BIND_EVENT_FN(FollowRenderableCamera::func));
}