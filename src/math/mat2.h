#ifndef __TLETC_Mat2__
#define __TLETC_Mat2__

#include "vec2.h"

//4 * 4 float matrix
struct Mat2f {
    union {
        float elements[2 * 2];
        Vec2 rows[2];
    };
    
    Mat2f();
    Mat2f(float identity);
    Mat2f(Vec2 row0, Vec2 row1);
    ~Mat2f();
    
    const Vec2& operator[](int index) const;
    Vec2& operator[](int index);
    
    
    void operator+=(const Mat2f& other);
    void operator-=(const Mat2f& other);
    void operator*=(const Mat2f& other);
    
    friend Mat2f operator+(Mat2f left, const Mat2f& right);
    friend Mat2f operator-(Mat2f left, const Mat2f& right);
    friend Mat2f operator*(Mat2f left, const Mat2f& right);
    
    private:
    void add(const Mat2f& other);
    void subtract(const Mat2f& other);
    void multiply(const Mat2f& other);
};

#endif