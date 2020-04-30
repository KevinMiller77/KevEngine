#include "OrthographicCameraController.h"
#include <core/KevInput.h>
#include <events/InputCodes.h>

OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
	: AspectRatio(aspectRatio), Camera(-AspectRatio * Zoom, AspectRatio * Zoom, -Zoom, Zoom), m_Rotation(rotation), movingCamera(false), savedMousePos(Vec2u(0, 0))
{
	time.Reset();
}

void OrthographicCameraController::OnUpdate()
{
	double ts = time.GetTimePassed();
    
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
                diffX = (int)(savedMousePos.x - x);
                
                if (diffX < 0)
                {
                    CamPos.x += cos(CamRot) * CamTranslationSpeed * ts * ((float)diffX / max(Zoom, 5.0f));
                }
                else
                {
                    CamPos.x += cos(CamRot) * CamTranslationSpeed * ts * ((float)diffX / max(Zoom, 5.0f));
                }
                
                diffY = (int)(savedMousePos.y - y);
                if (diffY < 0)
                {
                    CamPos.y -= cos(CamRot) * CamTranslationSpeed * ts * ((float)diffY / max(Zoom, 5.0f));
                }
                else
                {
                    CamPos.y -= cos(CamRot) * CamTranslationSpeed * ts * ((float)diffY / max(Zoom, 5.0f));
                }
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
    

	if (m_Rotation)
	{
		if (KevInput::IsKeyPressed(KEV_KEY_Q))
			CamRot += CamRotSpeed * ts;
		if (KevInput::IsKeyPressed(KEV_KEY_E))
			CamRot -= CamRotSpeed * ts;

		if (CamRot > 180.0f)
			CamRot -= 360.0f;
		else if (CamRot <= -180.0f)
			CamRot += 360.0f;

		Camera.SetRotation(CamRot);
	}

	if (KevInput::IsKeyPressed(KEV_KEY_R))
	{
		CamPos = Vec3f(0.0f, 0.0f, 0.0f);
		CamRot = 0;
		Zoom = 1.0f;
		Camera.SetProjection(-AspectRatio, AspectRatio, -Zoom, Zoom);
	}

	Camera.SetPosition(&CamPos);

	time.Reset();
}

void OrthographicCameraController::OnEvent(Event& e)
{

	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<MouseScrolledEvent>(KEV_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
	dispatcher.Dispatch<WindowResizeEvent>(KEV_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
}

bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
{
	Zoom -= e.getYOffset() * 0.1f;
	Zoom = Zoom > 0.1f ? Zoom : 0.1;
	Camera.SetProjection(-AspectRatio * AspectRatio, AspectRatio * Zoom, -Zoom, Zoom);
	return false;
}

bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
{

	AspectRatio = (float)e.getScreenSize().x / (float)e.getScreenSize().y;
	Camera.SetProjection(-AspectRatio * Zoom, AspectRatio * Zoom, -Zoom, Zoom);
	return false;
}
