#include "mat4.h"

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

Mat4f Mat4f::Orthographic(float left, float right, float top, float bottom, float near, float far) {
    Mat4f result(1.0f);
    result[0][0] = 2 / (right - left);
    result[0][3] = -1 * ((right + left) / (right - left));
    
    result[1][1] = 2 / (top - bottom);
    result[1][3] = -1 * ((top + bottom) / (top - bottom));
    
    result[2][2] = -2 / (far - near);
    result[2][3] = -1 * ((far + near) / (far - near));
    
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