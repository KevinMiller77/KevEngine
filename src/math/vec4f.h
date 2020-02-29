#ifndef __TLETC_VEC4__
#define __TLETC_VEC4__

//4 Float vector
struct Vec4f {
    union {
        struct {float x; float y; float z; float w;};
        float elements[4];
    };
    
    Vec4f();
    Vec4f(float x, float y, float z, float w);
    ~Vec4f();
    
    const float& operator[](int index) const;
    float& operator[](int index);
    
    void operator+=(const Vec4f& other);
    void operator-=(const Vec4f& other);
    void operator*=(const Vec4f& other);
    void operator/=(const Vec4f& other);
    
    friend Vec4f operator+(Vec4f left, Vec4f right);
    friend Vec4f operator-(Vec4f left, Vec4f right);
    friend Vec4f operator*(Vec4f left, Vec4f right);
    friend Vec4f operator/(Vec4f left, Vec4f right);
    
    private:
    void add(const Vec4f& other);
    void subtract(const Vec4f& other);
    void multiply(const Vec4f& other);
    void divide(const Vec4f& other);
};

#endif