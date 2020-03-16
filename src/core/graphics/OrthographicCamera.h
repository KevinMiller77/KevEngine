#ifndef __ORTHO_CAMERA__
#define __ORTHO_CAMERA__

#include <core/math/math.h>
#include <core/utils/Logging.h>

class OrthographicCamera
{
public:
	OrthographicCamera(float left, float right, float bottom, float top);

	void SetProjection(float left, float right, float bottom, float top);

	const Vec3f& GetPosition() const { return position; }
	void SetPosition(Vec3f& pos) { position = pos; RecalculateViewMatrix(); }

	float GetRotation() const { return rotation; }
	void SetRotation(float rot) { rotation = rot; RecalculateViewMatrix(); }

	const Mat4f& GetProjectionMatrix() const { return projectionMatrix; }
	const Mat4f& GetViewMatrix() const { return viewMatrix; }
	const Mat4f& GetViewProjectionMatrix() const { return viewProjMatrix; }
private:
	void RecalculateViewMatrix();
private:
	Mat4f projectionMatrix;
	Mat4f viewMatrix;
	Mat4f viewProjMatrix;

protected:
	Vec3f position = { 0.0f, 0.0f, 0.0f };
	float rotation = 0.0f;
};


#endif