#include "vec2.h"

#include <string.h>
#include <assert.h>

Vec2f::Vec2f() {
    memset(elements, 0, 2 * sizeof(float));
}

Vec2f::~Vec2f() {}

Vec2f::Vec2f(float x, float y) {
    elements[0] = x;
    elements[1] = y;
}

void Vec2f::add(const Vec2f& other) {
    elements[0] += other[0];
    elements[1] += other[1];
}

void Vec2f::subtract(const Vec2f& other) {
    elements[0] -= other[0];
    elements[1] -= other[1];
}

void Vec2f::multiply(const Vec2f& other) {
    elements[0] *= other[0];
    elements[1] *= other[1];
}

void Vec2f::divide(const Vec2f& other) {
    elements[0] /= other[0];
    elements[1] /= other[1];
}

const float& Vec2f::operator[](int index) const {
    assert(index >= 0 && index < 2);
    
    return elements[index];
}


float& Vec2f::operator[](int index) {
    assert(index >= 0 && index < 2);
    
    return elements[index];
}

void Vec2f::operator+=(const Vec2f& other) {
    add(other);
}

void Vec2f::operator-=(const Vec2f& other) {
    subtract(other);
}

void Vec2f::operator*=(const Vec2f& other) {
    multiply(other);
}

void Vec2f::operator/=(const Vec2f& other) {
    divide(other);
}

Vec2f operator+(Vec2f left, Vec2f right) {
    Vec2f result(left);
    result.add(right);
    return result;
}

Vec2f operator-(Vec2f left, Vec2f right) {
    Vec2f result(left);
    result.subtract(right);
    return result;
}

Vec2f operator*(Vec2f left, Vec2f right) {
    Vec2f result(left);
    result.multiply(right);
    return result;
}

Vec2f operator/(Vec2f left, Vec2f right) {
    Vec2f result(left);
    result.divide(right);
    return result;
}