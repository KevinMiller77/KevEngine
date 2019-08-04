#ifndef __TLETC_MAT4__
#define __TLETC_MAT4__

#include "vec4.h"

//4 * 4 float matrix
struct Mat4f {
    union {
        float elements[4 * 4];
        Vec4f rows[4];
    };
    
    Mat4f();
    Mat4f(float identity);
    Mat4f(Vec4f row0, Vec4f row1, Vec4f row2, Vec4f row3);
    ~Mat4f();
    
    static Mat4f Orthographic(float left, float right, float top, float bottom, float near, float far);
    
    const Vec4f& operator[](int index) const;
    Vec4f& operator[](int index);
    
    void operator+=(const Mat4f& other);
    void operator-=(const Mat4f& other);
    void operator*=(const Mat4f& other);
    
    friend Mat4f operator+(Mat4f left, const Mat4f& right);
    friend Mat4f operator-(Mat4f left, const Mat4f& right);
    friend Mat4f operator*(Mat4f left, const Mat4f& right);
    
    private:
    void add(const Mat4f& other);
    void subtract(const Mat4f& other);
    void multiply(const Mat4f& other);
};

#endif