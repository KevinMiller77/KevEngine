#ifndef __TLETC_Mat2__
#define __TLETC_Mat2__

#include <iostream>
#include <string.h>

#include "logging.h"
#include "vec2.h"

namespace tletc {
	//4 * 4 float matrix
	struct Mat2 {
		union {
			float elements[2 * 2];
			Vec2 rows[2];
		};

		Mat2();
		Mat2(float identity);
		~Mat2();

		const Vec2& operator[](int index) const;
		Vec2& operator[](int index);


		void operator+=(const Mat2& other);
		void operator-=(const Mat2& other);
		void operator*=(const Mat2& other);

		friend std::ostream& operator<<(std::ostream& stream, Mat2& matrix);

		friend Mat2 operator+(Mat2 left, const Mat2& right);
		friend Mat2 operator-(Mat2 left, const Mat2& right);
		friend Mat2 operator*(Mat2 left, const Mat2& right);
		
        private:
        void add(const Mat2& other);
		void subtract(const Mat2& other);
		void multiply(const Mat2& other);
	};
}

#endif