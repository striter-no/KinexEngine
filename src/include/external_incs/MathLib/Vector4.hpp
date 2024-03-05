#pragma once
#include "Vector3.hpp"

namespace eml{
    template<class T = float>
    class vec4{
        public:

        T x, y, z, w = 1;
        vec4(T a){x = a; y = a; z = a;}
        vec4(vec2<T> v, T a){x = v.x; y = v.y; z = a;}
        vec4(T a, vec2<T> v){x = a; y = v.x; z = v.y;}
        vec4(T x_, T y_, T z_, T w_ = 1){x = x_; y = y_; z = z_; w = w_;}
        vec4(vec3<T> v3, T w_ = 1){x = v3.x; y = v3.y; z = v3.z; w = w_;}
        const std::string str(){return "{"+std::to_string(x)+", "+std::to_string(y)+", "+std::to_string(z)+", "+std::to_string(w)+"}";}
        vec4(){};

        T &operator[](int ind){
            switch(ind){
                case 0: return x;
                case 1: return y;
                case 2: return z;
                case 3: return w;
            }
        }
    };

    template<class T = float> vec4<T> operator+(vec4<T> a, vec4<T> b){ return { a.x + b.x, a.y + b.y, a.z + b.z, a.w}; }
    template<class T = float> vec4<T> operator-(vec4<T> a, vec4<T> b){ return { a.x - b.x, a.y - b.y, a.z - b.z, a.w}; }
    template<class T = float> vec4<T> operator/(vec4<T> a, vec4<T> b){ return { a.x / b.x, a.y / b.y, a.z / b.z, a.w}; }
    template<class T = float> vec4<T> operator*(vec4<T> a, vec4<T> b){ return { a.x * b.x, a.y * b.y, a.z * b.z, a.w}; }

    template<class T = float> void operator+=(vec4<T> &a, vec4<T> b){a.x += b.x; a.y += b.y; a.z += b.z; }
    template<class T = float> void operator-=(vec4<T> &a, vec4<T> b){a.x -= b.x; a.y -= b.y; a.z -= b.z; }
    template<class T = float> void operator/=(vec4<T> &a, vec4<T> b){a.x /= b.x; a.y /= b.y; a.z /= b.z; }
    template<class T = float> void operator*=(vec4<T> &a, vec4<T> b){a.x *= b.x; a.y *= b.y; a.z *= b.z; }

    template<class T = float> vec4<T> operator+(vec4<T> a, T b){ return { a.x + b, a.y + b, a.z + b, a.w}; }
    template<class T = float> vec4<T> operator-(vec4<T> a, T b){ return { a.x - b, a.y - b, a.z - b, a.w}; }
    template<class T = float> vec4<T> operator/(vec4<T> a, T b){ return { a.x / b, a.y / b, a.z / b, a.w}; }
    template<class T = float> vec4<T> operator*(vec4<T> a, T b){ return { a.x * b, a.y * b, a.z * b, a.w}; }

    template<class T = float> vec4<T> operator+(T b, vec4<T> a){ return { b + a.x, b + a.y, b + a.z, a.w}; }
    template<class T = float> vec4<T> operator-(T b, vec4<T> a){ return { b - a.x, b - a.y, b - a.z, a.w}; }
    template<class T = float> vec4<T> operator/(T b, vec4<T> a){ return { b / a.x, b / a.y, b / a.z, a.w}; }
    template<class T = float> vec4<T> operator*(T b, vec4<T> a){ return { b * a.x, b * a.y, b * a.z, a.w}; }

    template<class T = float> void operator+=(vec4<T> &a, T b){a.x += b; a.y += b; a.z += b; }
    template<class T = float> void operator-=(vec4<T> &a, T b){a.x -= b; a.y -= b; a.z -= b; }
    template<class T = float> void operator/=(vec4<T> &a, T b){a.x /= b; a.y /= b; a.z /= b; }
    template<class T = float> void operator*=(vec4<T> &a, T b){a.x *= b; a.y *= b; a.z *= b; }

    template<class T = float> bool operator==(vec4<T> a, vec4<T> b){ return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w; }
    template<class T = float> bool operator!=(vec4<T> a, vec4<T> b){ return !(a == b);}
    template<class T = float> bool operator==(vec4<T> a, T b){ return a.x == b && a.y == b && a.z == b && a.w == b; }
    template<class T = float> bool operator!=(vec4<T> a, T b){ return !(a == b); }
    
    template<class T = float> vec4<T> operator-(vec4<T> a){ return {-a.x, -a.y, -a.z, -a.w}; }
}

#define vec4i vec4<int>
#define vec4f vec4<float>
#define vec4d vec4<double>