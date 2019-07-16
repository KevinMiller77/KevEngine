#include <vec3.h>

namespace tletc {
    Vec3::Vec3(){
        memset(elements, 0, 3 * sizeof(float));
    }

    Vec3::~Vec3(){}

    Vec3::Vec3(float x, float y, float z){
        elements[0] = x;
        elements[1] = y;
        elements[2] = z;

    }

    void Vec3::add(const Vec3& other)
    {
        elements[0] += other[0];
        elements[1] += other[1];
        elements[2] += other[2];
    }

    void Vec3::subtract(const Vec3& other)
    {
        elements[0] -= other[0];
        elements[1] -= other[1];
        elements[2] -= other[2];
    }

    void Vec3::multiply(const Vec3& other)
    {
        elements[0] *= other[0];
        elements[1] *= other[1];
        elements[2] *= other[2];
    }

    void Vec3::divide(const Vec3& other)
    {
        elements[0] /= other[0];
        elements[1] /= other[1];
        elements[2] /= other[2];
    }

    const float& Vec3::operator[](int index) const 
    {
        if (index < 3 && index > 0 ){
            return elements[index];
        }
        LOGE("ACCESS VIOLATION\n");
    }

    
    float& Vec3::operator[](int index)
    {
        if (index < 3 && index > 0 ){
            return elements[index];
        }
        LOGE("ACCESS VIOLATION\n");
    }
    
    void Vec3::operator+=(const Vec3& other)
    {
        add(other);
    }

    void Vec3::operator-=(const Vec3& other)
    {
        subtract(other);
    }

    void Vec3::operator*=(const Vec3& other)
    {
        multiply(other);
    }

    void Vec3::operator/=(const Vec3& other) 
    {
        divide(other);
    }

    std::ostream& operator<<(std::ostream& stream, Vec3& vector)
    {
        stream << "["   << vector[0] << ", "
                        << vector[1] << ", "
                        << vector[2] << "]\n";
        return stream;
    }

    Vec3 operator+(Vec3 left, Vec3 right)
    {
        left.add(right);
    }

    Vec3 operator-(Vec3 left, Vec3 right)
    {
        left.subtract(right);
    }

    Vec3 operator*(Vec3 left, Vec3 right)
    {
        left.multiply(right);
    }

    Vec3 operator/(Vec3 left, Vec3 right)
    {
        left.divide(right);
    }
}