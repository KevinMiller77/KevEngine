#pragma once

#include "OrthographicCamera.h"

#include "../../events/WindowEvent.h"
#include "../../events/MouseEvent.h"
#include <utils/Timer.h>

class OrthographicCameraController
{
public:
	OrthographicCameraController(float aspectRatio, bool rotation = false);

	void OnUpdate();
	void OnEvent(Event& e);

	OrthographicCamera& GetCamera() { return Camera; }
	const OrthographicCamera& GetCamera() const { return Camera; }

	float GetZoomLevel() const { return Zoom; }
	void SetZoomLevel(float level) { Zoom = level; }
private:
	bool OnMouseScrolled(MouseScrolledEvent& e);
	bool OnWindowResized(WindowResizeEvent& e);
private:
	float AspectRatio;
	float Zoom = 1.0f;
	Timer time;
	OrthographicCamera Camera;

	bool m_Rotation;

	Vec3f CamPos = { 0.0f, 0.0f, 0.0f };
	float CamRot = 0.0f; //In degrees, in the anti-clockwise direction
	float CamTranslationSpeed = 5.0f, CamRotSpeed = 180.0f;
};
