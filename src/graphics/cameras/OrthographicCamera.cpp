#include "OrthographicCamera.h"

OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
	: projectionMatrix(Mat4f::orthographic(left, right, bottom, top, -1.0f, 1.0f)), viewMatrix(1.0f)
{
	projectionMatrix.printMatrix();
	viewProjMatrix = projectionMatrix * viewMatrix;
}

void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
{

	projectionMatrix = Mat4f::orthographic(left, right, bottom, top, -1.0f, 1.0f);
	viewProjMatrix = projectionMatrix * viewMatrix;
}

void OrthographicCamera::RecalculateViewMatrix()
{
	Mat4f transform = Mat4f::translation(position) * Mat4f::rotation(rotation, Vec3f(0, 0, 1));
	//transform.printMatrix();
	viewMatrix = transform.invertMatrix();
	//viewMatrix.printMatrix();
	viewProjMatrix = projectionMatrix * viewMatrix;
}
