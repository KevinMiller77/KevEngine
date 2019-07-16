#include "mat2.h"

namespace tletc {
	Mat2::Mat2()
	{
		memset(elements, 0, 2 * 2 * sizeof(float));
	}

	Mat2::Mat2(float identity)
	{
		memset(elements, 0, 2 * 2 * sizeof(float));
		elements[0 * 2 + 0] = identity;
		elements[1 * 2 + 1] = identity;
	}

	Mat2::~Mat2() {}

	void Mat2::add(const Mat2& other)
	{
		for (int i = 0; i < 2 * 2; i++) {
			elements[i] += other.elements[i];
		}
	}

	void Mat2::subtract(const Mat2& other)
	{
		for (int i = 0; i < 2 * 2; i++) {
			elements[i] -= other.elements[i];
		}
	}

	void Mat2::multiply(const Mat2& other)
	{
		float result[4];

		for (int row = 0; row < 2; row++) {
			for (int col = 0; col < 2; col++) {
				//Dot-product for each element of result
				float resultSum = 0;
				for (int i = 0; i < 2; i++) {
					resultSum += elements[row * 2 + i] * other.elements[i * 2 + col];
				}
				result[row * 2 + col] = resultSum;
			}
		}

		memcpy(elements, result, 2 * 2 * sizeof(float));
	}

	const Vec2& Mat2::operator[](int index) const
	{
		if (index < 2 && index >= 0) {
			return rows[index];
		}
		LOGE("ACCESS VIOLATION\n");
	}

	Vec2& Mat2::operator[](int index)
	{
		if (index < 2 && index >= 0) {
			return rows[index];
		}
		LOGE("ACCESS VIOLATION\n");
	}

	void Mat2::operator+=(const Mat2& other)
	{
		add(other);
	}

	void Mat2::operator-=(const Mat2& other)
	{
		subtract(other);
	}

	void Mat2::operator*=(const Mat2& other)
	{
		multiply(other);
	}

	std::ostream& operator<<(std::ostream& stream, Mat2& matrix)
	{
		stream << matrix[0] << std::endl << matrix[1] << std::endl;
		return stream;
	}

	Mat2 operator+(Mat2 left, const Mat2& right)
	{
		left.add(right);
		return left;
	}

	Mat2 operator-(Mat2 left, const Mat2& right)
	{
		left.subtract(right);
		return left;
	}

	Mat2 operator*(Mat2 left, const Mat2& right)
	{
		left.multiply(right);
		return left;
	}
}