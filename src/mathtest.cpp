#include <stdio.h>

#include "math/math.h"

int main() {
    Vec2f vec2(1.0f, 2.0f);
    Vec3f vec3(1.0f, 2.0f, 3.0f);
    Vec4f vec4(1.0f, 2.0f, 3.0f, 4.0f);
    Mat2f mat2_1(2.0f);
    Mat2f mat2_2(Vec2f(1.0f, 2.0f), Vec2f(3.0f, 4.0f));
    Mat4f mat4_1(2.0f);
    Mat4f mat4_2(Vec4f(1.0f, 2.0f, 3.0f, 4.0f), Vec4f(1.0f, 2.0f, 3.0f, 4.0f), Vec4f(1.0f, 2.0f, 3.0f, 4.0f), Vec4f(1.0f, 2.0f, 3.0f, 4.0f));
}