#include <vec2.h>

namespace tletc {
    Vec2::Vec2(){
        memset(elements, 0, 2 * sizeof(float));
    }

    Vec2::~Vec2(){}

    Vec2::Vec2(float x, float y){
        elements[0] = x;
        elements[1] = y;
    }

    void Vec2::add(const Vec2& other)
    {
        elements[0] += other[0];
        elements[1] += other[1];
    }

    void Vec2::subtract(const Vec2& other)
    {
        elements[0] -= other[0];
        elements[1] -= other[1];
    }

    void Vec2::multiply(const Vec2& other)
    {
        elements[0] *= other[0];
        elements[1] *= other[1];
    }

    void Vec2::divide(const Vec2& other)
    {
        elements[0] /= other[0];
        elements[1] /= other[1];
    }

    const float& Vec2::operator[](int index) const 
    {
        if (index < 2 && index > 0 ){
            return elements[index];
        }
        LOGE("ACCESS VIOLATION\n");
    }

    
    float& Vec2::operator[](int index)
    {
        if (index < 2 && index > 0 ){
            return elements[index];
        }
        LOGE("ACCESS VIOLATION\n");
    }
    
    void Vec2::operator+=(const Vec2& other)
    {
        add(other);
    }

    void Vec2::operator-=(const Vec2& other)
    {
        subtract(other);
    }

    void Vec2::operator*=(const Vec2& other)
    {
        multiply(other);
    }

    void Vec2::operator/=(const Vec2& other) 
    {
        divide(other);
    }

    std::ostream& operator<<(std::ostream& stream, Vec2& vector)
    {
        stream << "["   << vector[0] << ", "
                        << vector[1] << "]\n";
        return stream;
    }

    Vec2 operator+(Vec2 left, Vec2 right)
    {
        left.add(right);
    }

    Vec2 operator-(Vec2 left, Vec2 right)
    {
        left.subtract(right);
    }

    Vec2 operator*(Vec2 left, Vec2 right)
    {
        left.multiply(right);
    }

    Vec2 operator/(Vec2 left, Vec2 right)
    {
        left.divide(right);
    }
}