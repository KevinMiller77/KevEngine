#ifndef __TLETC_Vec2__
#define __TLETC_Vec2__

#include <iostream>
#include <string.h>
#include "logging.h"

namespace tletc {
    //3 Float vector
    struct Vec2{
        union{
            float elements[2];
            struct {float x; float y;};
        };
        
        Vec2();
        Vec2(float x, float y);
        ~Vec2();
        
        const float& operator[](int index) const;
        float& operator[](int index);
        
        void operator+=(const Vec2& other);
        void operator-=(const Vec2& other);
        void operator*=(const Vec2& other);
        void operator/=(const Vec2& other);
        
        friend std::ostream& operator<<(std::ostream& stream, Vec2& vector);
        
        friend Vec2 operator+(Vec2 left, Vec2 right);
        friend Vec2 operator-(Vec2 left, Vec2 right);
        friend Vec2 operator*(Vec2 left, Vec2 right);
        friend Vec2 operator/(Vec2 left, Vec2 right);
        
        private:
        void add(const Vec2& other);
        void subtract(const Vec2& other);
        void multiply(const Vec2& other);
        void divide(const Vec2& other);
    };
}


#endif