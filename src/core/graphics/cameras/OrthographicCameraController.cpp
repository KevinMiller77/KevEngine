#include "OrthographicCameraController.h"
#include <core/events/WindowsInputCodes.h>
#include <core/Input.h>

OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
	: AspectRatio(aspectRatio), Camera(-AspectRatio * Zoom, AspectRatio * Zoom, -Zoom, Zoom), m_Rotation(rotation)
{
	time.reset();
}

void OrthographicCameraController::OnUpdate()
{
	double ts = time.getTimePassed();
	if (Input::IsKeyPressed(KEV_KEY_A))
	{
		CamPos.x -= cos(CamRot) * CamTranslationSpeed * ts;
		CamPos.y -= sin(CamRot) * CamTranslationSpeed * ts;
	}
	else if (Input::IsKeyPressed(KEV_KEY_D))
	{
		CamPos.x += cos(CamRot) * CamTranslationSpeed * ts;
		CamPos.y += sin(CamRot) * CamTranslationSpeed * ts;
	}

	if (Input::IsKeyPressed(KEV_KEY_W))
	{
		CamPos.x += -sin(CamRot) * CamTranslationSpeed * ts;
		CamPos.y += cos(CamRot) * CamTranslationSpeed * ts;
	}
	else if (Input::IsKeyPressed(KEV_KEY_S))
	{
		CamPos.x -= -sin(CamRot) * CamTranslationSpeed * ts;
		CamPos.y -= cos(CamRot) * CamTranslationSpeed * ts;
	}

	if (m_Rotation)
	{
		if (Input::IsKeyPressed(KEV_KEY_Q))
			CamRot += CamRotSpeed * ts;
		if (Input::IsKeyPressed(KEV_KEY_E))
			CamRot -= CamRotSpeed * ts;

		if (CamRot > 180.0f)
			CamRot -= 360.0f;
		else if (CamRot <= -180.0f)
			CamRot += 360.0f;

		Camera.SetRotation(CamRot);
	}

	if (Input::IsKeyPressed(KEV_KEY_R))
	{
		CamPos = Vec3f(0.0f, 0.0f, 0.0f);
		CamRot = 0;
		Zoom = 1.0f;
		Camera.SetProjection(-AspectRatio, AspectRatio, -Zoom, Zoom);
	}

	Camera.SetPosition(CamPos);

	time.reset();
}

void OrthographicCameraController::OnEvent(Event& e)
{

	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<MouseScrolledEvent>(KEV_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
	dispatcher.Dispatch<WindowResizeEvent>(KEV_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
}

bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
{
	Zoom -= ((float)e.getYOffset() / 65536.0f) * 0.1f;
	Zoom = Zoom > 0.1f ? Zoom : 0.1f;
	Camera.SetProjection(-AspectRatio * Zoom, AspectRatio * Zoom, -Zoom, Zoom);
	return false;
}

bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
{

	AspectRatio = (float)e.getScreenSize().x / (float)e.getScreenSize().y;
	Camera.SetProjection(-AspectRatio * Zoom, AspectRatio * Zoom, -Zoom, Zoom);
	return false;
}