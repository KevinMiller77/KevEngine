#include "mat4f.h"

#include <string.h>
#include <assert.h>

Mat4f::Mat4f() {
    memset(elements, 0, 4 * 4 * sizeof(float));
}

Mat4f::Mat4f(float identity) {
    memset(elements, 0, 4 * 4 * sizeof(float));
    elements[0 * 4 + 0] = identity;
    elements[1 * 4 + 1] = identity;
    elements[2 * 4 + 2] = identity;
    elements[3 * 4 + 3] = identity;
}

Mat4f::Mat4f(Vec4f row0, Vec4f row1, Vec4f row2, Vec4f row3) {
    memcpy(rows[0].elements, row0.elements, 4 * sizeof(float));
    memcpy(rows[1].elements, row1.elements, 4 * sizeof(float));
    memcpy(rows[2].elements, row2.elements, 4 * sizeof(float));
    memcpy(rows[3].elements, row3.elements, 4 * sizeof(float));
}

Mat4f::~Mat4f() {}

Mat4f Mat4f::orthographic(float left, float right, float top, float bottom, float near, float far) {
    Mat4f result(1.0f);

	result.elements[0 + 0 * 4] = 2.0f / (right - left);

	result.elements[1 + 1 * 4] = 2.0f / (top - bottom);

	result.elements[2 + 2 * 4] = 2.0f / (near - far);

	result.elements[0 + 3 * 4] = (left + right) / (left - right);
	result.elements[1 + 3 * 4] = (bottom + top) / (bottom - top);
	result.elements[2 + 3 * 4] = (far + near) / (far - near);

	return result;
}

void Mat4f::add(const Mat4f& other) {
    for (int i = 0; i < 4 * 4; i++) {
        elements[i] += other.elements[i];
    }
}

void Mat4f::subtract(const Mat4f& other) {
    for (int i = 0; i < 4 * 4; i++) {
        elements[i] -= other.elements[i];
    }
}

void Mat4f::multiply(const Mat4f& other) {
    float result[16];
    
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            //Dot-product for each element of result
            float resultSum = 0;
            for (int i = 0; i < 4; i++) {
                resultSum += elements[row * 4 + i] * other.elements[i * 4 + col];
            }
            result[row * 4 + col] = resultSum;
        }
    }
    
    memcpy(elements, result, 4 * 4 * sizeof(float));
}

const Vec4f& Mat4f::operator[](int index) const {
    assert(index >= 0 && index < 4);
    
    return rows[index];
}

Vec4f& Mat4f::operator[](int index) {
    assert(index >= 0 && index < 4);
    
    return rows[index];
}

void Mat4f::operator+=(const Mat4f& other) {
    add(other);
}

void Mat4f::operator-=(const Mat4f& other) {
    subtract(other);
}

void Mat4f::operator*=(const Mat4f& other) {
    multiply(other);
}

Mat4f operator+(Mat4f left, const Mat4f& right) {
    left.add(right);
    return left;
}

Mat4f operator-(Mat4f left, const Mat4f& right) {
    left.subtract(right);
    return left;
}

Mat4f operator*(Mat4f left, const Mat4f& right) {
    left.multiply(right);
    return left;
}

Mat4f Mat4f::perspective(float fov, float aspectRatio, float near, float far)
	{
		Mat4f result(1.0f);

		float q = (float) (1.0f / tan(0.5f * fov * (3.14123f / 180.0f)));
		float a = (float) (q / aspectRatio);

		float b = (near + far) / (near - far);
		float c = (2.0f * near * far) / (near - far);

		result.elements[0 + 0 * 4] = a;
		result.elements[1 + 1 * 4] = q;
		result.elements[2 + 2 * 4] = b;
		result.elements[3 + 2 * 4] = -1.0f;
		result.elements[2 + 3 * 4] = c;

		return result;
	}

	Mat4f Mat4f::translation(const Vec3f& translation)
	{
		Mat4f result(1.0f);

		result.elements[0 + 3 * 4] = translation.x;
		result.elements[1 + 3 * 4] = translation.y;
		result.elements[2 + 3 * 4] = translation.z;

		return result;
	}

	Mat4f Mat4f::rotation(float angle, const Vec3f& axis)
	{
		Mat4f result(1.0f);

		float r = angle * (3.14123f / 180.0f);
		float c = (float) (cos(r));
		float s = (float) (sin(r));
		float omc = 1.0f - c;
		
		float x = axis.x;
		float y = axis.y;
		float z = axis.z;

		result.elements[0 + 0 * 4] = x * omc + c;
		result.elements[1 + 0 * 4] = y * x * omc + z * s;
		result.elements[2 + 0 * 4] = x * z * omc - y * s;

		result.elements[0 + 1 * 4] = x * y * omc - z * s;
		result.elements[1 + 1 * 4] = y * omc + c;
		result.elements[2 + 1 * 4] = y * z * omc + x * s;

		result.elements[0 + 2 * 4] = x * z * omc + y * s;
		result.elements[1 + 2 * 4] = y * z * omc - x * s;
		result.elements[2 + 2 * 4] = z * omc + c;
		
		return result;
	}

	Mat4f Mat4f::scale(const Vec3f& scale)
	{
		Mat4f result(1.0f);

		result.elements[0 + 0 * 4] = scale.x;
		result.elements[1 + 1 * 4] = scale.y;
		result.elements[2 + 2 * 4] = scale.z;

		return result;
	}