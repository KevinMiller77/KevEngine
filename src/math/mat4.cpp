#include "mat4.h"

namespace tletc {
	Mat4::Mat4()
	{
		memset(elements, 0, 4 * 4 * sizeof(float));
	}

	Mat4::Mat4(float identity)
	{
		memset(elements, 0, 4 * 4 * sizeof(float));
		elements[0 * 4 + 0] = identity;
		elements[1 * 4 + 1] = identity;
		elements[2 * 4 + 2] = identity;
		elements[3 * 4 + 3] = identity;
	}

	Mat4::~Mat4() {}

	Mat4 Mat4::Orthographic(float left, float right, float top, float bottom, float near, float far)
	{
		Mat4 result(1.0f);
		result[0][0] = 2 / (right - left);
		result[0][3] = -1 * ((right + left) / (right - left));

		result[1][1] = 2 / (top - bottom);
		result[1][3] = -1 * ((top + bottom) / (top - bottom));

		result[2][2] = -2 / (far - near);
		result[2][3] = -1 * ((far + near) / (far - near));

		return result;
	}

	void Mat4::add(const Mat4& other)
	{
		for (int i = 0; i < 4 * 4; i++) {
			elements[i] += other.elements[i];
		}
	}

	void Mat4::subtract(const Mat4& other)
	{
		for (int i = 0; i < 4 * 4; i++) {
			elements[i] -= other.elements[i];
		}
	}

	void Mat4::multiply(const Mat4& other)
	{
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

	const Vec4& Mat4::operator[](int index) const
	{
		if (index < 4 && index >= 0) {
			return rows[index];
		}
		LOGE("ACCESS VIOLATION\n");
	}

	Vec4& Mat4::operator[](int index)
	{
		if (index < 4 && index >= 0) {
			return rows[index];
		}
		LOGE("ACCESS VIOLATION\n");
	}

	void Mat4::operator+=(const Mat4& other)
	{
		add(other);
	}

	void Mat4::operator-=(const Mat4& other)
	{
		subtract(other);
	}

	void Mat4::operator*=(const Mat4& other)
	{
		multiply(other);
	}

	std::ostream& operator<<(std::ostream& stream, Mat4& matrix)
	{
		stream << matrix[0] << std::endl << matrix[1] << std::endl << matrix[2] << std::endl << matrix[3];
		return stream;
	}

	Mat4 operator+(Mat4 left, const Mat4& right)
	{
		left.add(right);
		return left;
	}

	Mat4 operator-(Mat4 left, const Mat4& right)
	{
		left.subtract(right);
		return left;
	}

	Mat4 operator*(Mat4 left, const Mat4& right)
	{
		left.multiply(right);
		return left;
	}
}