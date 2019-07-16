#ifndef __TLETC_MAT4__
#define __TLETC_MAT4__

#include <iostream>
#include <string.h>

#include "logging.h"
#include "vec4.h"

namespace tletc {
	//4 * 4 float matrix
	struct Mat4 {
		union {
			float elements[4 * 4];
			Vec4 rows[4];
		};

		Mat4();
		Mat4(float identity);
		~Mat4();

		static Mat4 Orthographic(float left, float right, float top, float bottom, float near, float far);
		static Vec4 Transform(Vec4 magnitude);

		const Vec4& operator[](int index) const;
		Vec4& operator[](int index);

		void operator+=(const Mat4& other);
		void operator-=(const Mat4& other);
		void operator*=(const Mat4& other);

		friend std::ostream& operator<<(std::ostream& stream, Mat4& matrix);

		friend Mat4 operator+(Mat4 left, const Mat4& right);
		friend Mat4 operator-(Mat4 left, const Mat4& right);
		friend Mat4 operator*(Mat4 left, const Mat4& right);
		
        private:
        void add(const Mat4& other);
		void subtract(const Mat4& other);
		void multiply(const Mat4& other);
	};
}

#endif