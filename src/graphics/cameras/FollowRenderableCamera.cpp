#include "FollowRenderableCamera.h"

FollowRenderableCamera::FollowRenderableCamera(float horizontalMax, float verticalMax)
    : Camera(-horizontalMax, horizontalMax, -verticalMax, verticalMax)
{
    movingCamera = false;
    time.Reset();
}

FollowRenderableCamera::FollowRenderableCamera(float horizontalMax, float verticalMax, Renderable2D* renderable)
    : Camera(-horizontalMax, horizontalMax, -verticalMax, verticalMax), renderableToFollow(renderable), savedMousePos(0, 0)
{
    movingCamera = false;
    time.Reset();
}
    
void FollowRenderableCamera::OnUpdate()
{
    if (renderableToFollow == nullptr)
    {
//        return;
    }
    
	double ts = time.GetTimePassed();
    Vec3f camPos = Camera.GetPosition();
    
    if(KevInput::IsMouseButtonPressed(MouseCode::Button2))
    {
        if (savedMousePos.x == 0 && savedMousePos.y == 0)
        {
            
            savedMousePos.x = KevInput::GetMousePos().x;
            savedMousePos.y = KevInput::GetMousePos().y;
        }
        int diffX = 0;
        int diffY = 0;
        if (movingCamera)
        {
            int x = KevInput::GetMousePos().x;
            int y = KevInput::GetMousePos().y;
            
            if (savedMousePos.x - x == 0 && savedMousePos.y - y == 0)
            {
            }
            else
            {
                Vec3f newCamPos = Vec3f(Camera.GetPosition().x, Camera.GetPosition().y, Camera.GetPosition().z);
                diffX = (int)(savedMousePos.x - x);
                
                if (diffX < 0)
                {
                    LOG_INF("Moving\n");
                    newCamPos.x += ts * ((float)diffX / max(Zoom, 5.0f));
                }
                else
                {
                    LOG_INF("Moving\n");
                    newCamPos.x += ts * ((float)diffX / max(Zoom, 5.0f));
                }
                
                diffY = (int)(savedMousePos.y - y);
                if (diffY < 0)
                {
                    LOG_INF("Moving\n");
                    newCamPos.y -= ts * ((float)diffY / max(Zoom, 5.0f));
                }
                else
                {
                    LOG_INF("Moving\n");
                    newCamPos.y -= ts * ((float)diffY / max(Zoom, 5.0f));
                }
                Camera.SetPosition(&newCamPos);
                
            }
            
            savedMousePos.x = x;
            savedMousePos.y = y;
            
        }
        movingCamera = true;
    }
    else
    {
        savedMousePos.x = 0;
        savedMousePos.y = 0;
        movingCamera = false;
    }
    
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
