#include "OrthographicCameraController.h"
#include <core/KevInput.h>
#include <events/InputCodes.h>

OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
	: AspectRatio(aspectRatio), Camera(-AspectRatio * Zoom, AspectRatio * Zoom, -Zoom, Zoom), m_Rotation(rotation)
{
	time.Reset();
}

void OrthographicCameraController::OnUpdate()
{
	double ts = time.GetTimePassed();
	if (KevInput::IsKeyPressed(KEV_KEY_A))
	{
		CamPos.x -= cos(CamRot) * CamTranslationSpeed * ts;
		CamPos.y -= sin(CamRot) * CamTranslationSpeed * ts;
	}
	else if (KevInput::IsKeyPressed(KEV_KEY_D))
	{
		CamPos.x += cos(CamRot) * CamTranslationSpeed * ts;
		CamPos.y += sin(CamRot) * CamTranslationSpeed * ts;
	}

	if (KevInput::IsKeyPressed(KEV_KEY_W))
	{
		CamPos.x += -sin(CamRot) * CamTranslationSpeed * ts;
		CamPos.y += cos(CamRot) * CamTranslationSpeed * ts;
	}
	else if (KevInput::IsKeyPressed(KEV_KEY_S))
	{
		CamPos.x -= -sin(CamRot) * CamTranslationSpeed * ts;
		CamPos.y -= cos(CamRot) * CamTranslationSpeed * ts;
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
	Zoom -= e.getYOffset() * 0.25f;
	Zoom = Zoom > 0.25f ? Zoom : 0.25;
	Camera.SetProjection(-AspectRatio * AspectRatio, AspectRatio * Zoom, -Zoom, Zoom);
	return false;
}

bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
{

	AspectRatio = (float)e.getScreenSize().x / (float)e.getScreenSize().y;
	Camera.SetProjection(-AspectRatio * Zoom, AspectRatio * Zoom, -Zoom, Zoom);
	return false;
}