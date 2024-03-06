#pragma once
#include "Vector2.hpp"

namespace eml{
    template<class T = float>
    class vec3{
        public:

        T x, y, z;
        vec3(T a){x = a; y = a; z = a;}
        vec3(vec2<T> v, T a){x = v.x; y = v.y; z = a;}
        vec3(T a, vec2<T> v){x = a; y = v.x; z = v.y;}
        vec3(T x_, T y_, T z_){x = x_; y = y_; z = z_;}
        vec3(){};
        const std::string str() const {return "{"+std::to_string(x)+", "+std::to_string(y)+", "+std::to_string(z)+"}";}
    
        T &operator[](int ind){
            switch(ind){
                case 0: return x;
                case 1: return y;
                case 2: return z;
            }
        }
    };

    template<class T = float> vec3<T> operator+(vec3<T> a, vec3<T> b){ return { a.x + b.x, a.y + b.y, a.z + b.z}; }
    template<class T = float> vec3<T> operator-(vec3<T> a, vec3<T> b){ return { a.x - b.x, a.y - b.y, a.z - b.z}; }
    template<class T = float> vec3<T> operator/(vec3<T> a, vec3<T> b){ return { a.x / b.x, a.y / b.y, a.z / b.z}; }
    template<class T = float> vec3<T> operator*(vec3<T> a, vec3<T> b){ return { a.x * b.x, a.y * b.y, a.z * b.z}; }

    template<class T = float> void operator+=(vec3<T> &a, vec3<T> b){a.x += b.x; a.y += b.y; a.z += b.z; }
    template<class T = float> void operator-=(vec3<T> &a, vec3<T> b){a.x -= b.x; a.y -= b.y; a.z -= b.z; }
    template<class T = float> void operator/=(vec3<T> &a, vec3<T> b){a.x /= b.x; a.y /= b.y; a.z /= b.z; }
    template<class T = float> void operator*=(vec3<T> &a, vec3<T> b){a.x *= b.x; a.y *= b.y; a.z *= b.z; }

    template<class T = float> vec3<T> operator+(vec3<T> a, T b){ return { a.x + b, a.y + b, a.z + b}; }
    template<class T = float> vec3<T> operator-(vec3<T> a, T b){ return { a.x - b, a.y - b, a.z - b}; }
    template<class T = float> vec3<T> operator/(vec3<T> a, T b){ return { a.x / b, a.y / b, a.z / b}; }
    template<class T = float> vec3<T> operator*(vec3<T> a, T b){ return { a.x * b, a.y * b, a.z * b}; }

    template<class T = float> vec3<T> operator+(T b, vec3<T> a){ return { b + a.x, b + a.y, b + a.z}; }
    template<class T = float> vec3<T> operator-(T b, vec3<T> a){ return { b - a.x, b - a.y, b - a.z}; }
    template<class T = float> vec3<T> operator/(T b, vec3<T> a){ return { b / a.x, b / a.y, b / a.z}; }
    template<class T = float> vec3<T> operator*(T b, vec3<T> a){ return { b * a.x, b * a.y, b * a.z}; }

    template<class T = float> void operator+=(vec3<T> &a, T b){a.x += b; a.y += b; a.z += b; }
    template<class T = float> void operator-=(vec3<T> &a, T b){a.x -= b; a.y -= b; a.z -= b; }
    template<class T = float> void operator/=(vec3<T> &a, T b){a.x /= b; a.y /= b; a.z /= b; }
    template<class T = float> void operator*=(vec3<T> &a, T b){a.x *= b; a.y *= b; a.z *= b; }

    template<class T = float> bool operator==(vec3<T> a, vec3<T> b){ return a.x == b.x && a.y == b.y && a.z == b.z; }
    template<class T = float> bool operator!=(vec3<T> a, vec3<T> b){ return !(a == b);}
    template<class T = float> bool operator==(vec3<T> a, T b){ return a.x == b && a.y == b && a.z == b; }
    template<class T = float> bool operator!=(vec3<T> a, T b){ return !(a == b); }
    template<class T = float> vec3<T> operator-(vec3<T> a){ return {-a.x, -a.y, -a.z}; }
}

#define vec3i vec3<int>
#define vec3f vec3<float>
#define vec3d vec3<double>