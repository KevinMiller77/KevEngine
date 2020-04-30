#ifndef __FOLLOW_RENDERABLE_CAMERA__
#define __FOLLOW_RENDERABLE_CAMERA__

#include "OrthographicCamera.h"
#include <graphics/renderables/Renderable2D.h>
#include <events/Event.h>
#include <events/KeyEvent.h>
#include <utils/Timer.h>

class FollowRenderableCamera
{
public:

    FollowRenderableCamera(float horizontalMax, float verticalMax);
    FollowRenderableCamera(float horizontalMax, float verticalMax, Renderable2D* renderable);
    
	void OnUpdate();
	void OnEvent(Event& e);
    
	OrthographicCamera& GetCamera() { return Camera; }
	const OrthographicCamera& GetCamera() const { return Camera; }

	float GetZoomLevel() const { return Zoom; }
	void SetZoomLevel(float level) { Zoom = level; }

    void SetRenderable(Renderable2D* renderable) { renderableToFollow = renderable; }
    Renderable2D* GetRenderable() const { return renderableToFollow; }

	bool func (KeyPressedEvent& e);

private:
    float vertical, horizontal;
	float Zoom = 1.0f;
	Timer time;
	OrthographicCamera Camera;
    Renderable2D* renderableToFollow = nullptr;
    bool movingCamera;
    Vec2u savedMousePos;

	float CamTranslationSpeed = 1.0f;
};

#endif
