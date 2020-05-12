#include "Kev2DCamera.h"

Kev2DCamera::Kev2DCamera(float horizontalMax, float verticalMax)
    : Camera(-horizontalMax, horizontalMax, -verticalMax, verticalMax)
{
    movingCamera = false;
    time.Reset();
}

Kev2DCamera::Kev2DCamera(float horizontalMax, float verticalMax, Renderable2D* renderable)
    : Camera(-horizontalMax, horizontalMax, -verticalMax, verticalMax), renderableToFollow(renderable), savedMousePos(0, 0)
{
    movingCamera = false;
    time.Reset();
}
    
void Kev2DCamera::OnUpdate()
{
    if (!movable)
    {
        time.Reset();
        return;
    }
    
	double ts = time.GetTimePassed();
    Vec3f camPos = Camera.GetPosition();
    
    if(KevInput::IsMouseButtonPressed(MouseCode::Button2) || (KevInput::IsKeyPressed(KeyCode::LeftControl) && KevInput::IsMouseButtonPressed(MouseCode::ButtonLeft)))
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
                    newCamPos.x += ts * ((float)diffX / max(Zoom, 5.0f));
                }
                else
                {
                    newCamPos.x += ts * ((float)diffX / max(Zoom, 5.0f));
                }
                
                diffY = (int)(savedMousePos.y - y);
                if (diffY < 0)
                {
                    newCamPos.y -= ts * ((float)diffY / max(Zoom, 5.0f));
                }
                else
                {
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

bool Kev2DCamera::func (KeyPressedEvent& e)
{
    // if (e.GetKeyCode() == (int)KEV_KEY_D)
    //     Camera.SetPosition(new Vec3f(Camera.GetPosition().x + 0.5f, Camera.GetPosition().y, Camera.GetPosition().z));

    // if (e.GetKeyCode() == (int)KEV_KEY_A)
    //     Camera.SetPosition(new Vec3f(Camera.GetPosition().x - 0.5f, Camera.GetPosition().y, Camera.GetPosition().z));

    return false;
}

void Kev2DCamera::OnEvent(Event& e)
{
    EventDispatcher dispatch(e);
    dispatch.Dispatch<KeyPressedEvent>(KEV_BIND_EVENT_FN(Kev2DCamera::func));
    dispatch.Dispatch<MouseScrolledEvent>(KEV_BIND_EVENT_FN(Kev2DCamera::OnMouseScrolled));
}

bool Kev2DCamera::OnMouseScrolled(MouseScrolledEvent& e)
{
    if (!movable)
    {
        return false;
    }
    Zoom -= e.getYOffset() * 0.01f;
    Zoom = Zoom > 0.1f ? Zoom : 0.1f;
    Zoom = Zoom > 2.8f ? 2.8f : Zoom;
    Camera.SetProjection(-16 * Zoom, 16 * Zoom, -9 * Zoom, 9 * Zoom);
    return false;
}
