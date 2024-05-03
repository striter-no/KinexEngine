#pragma once
#include <string>

namespace eml{
    template<class T = float>
    class vec2{
        public:
        T x, y;
        vec2(T a){x = a; y = a;}
        vec2(T x_, T y_){x = x_; y = y_;}
        vec2(){x = 0; y = 0;};
        const std::string str() const {return "{"+std::to_string(x)+", "+std::to_string(y)+"}";}
    
        T &operator[](int ind){
            switch(ind){
                case 0: return x;
                case 1: return y;
            }
        }
    };

    template<class T = float> vec2<T> operator+(vec2<T> a, vec2<T> b){ return { a.x + b.x, a.y + b.y}; }
    template<class T = float> vec2<T> operator-(vec2<T> a, vec2<T> b){ return { a.x - b.x, a.y - b.y}; }
    template<class T = float> vec2<T> operator/(vec2<T> a, vec2<T> b){ return { a.x / b.x, a.y / b.y}; }
    template<class T = float> vec2<T> operator*(vec2<T> a, vec2<T> b){ return { a.x * b.x, a.y * b.y}; }

    template<class T = float> void operator+=(vec2<T> &a, vec2<T> b){a.x += b.x; a.y += b.y; }
    template<class T = float> void operator-=(vec2<T> &a, vec2<T> b){a.x -= b.x; a.y -= b.y; }
    template<class T = float> void operator/=(vec2<T> &a, vec2<T> b){a.x /= b.x; a.y /= b.y; }
    template<class T = float> void operator*=(vec2<T> &a, vec2<T> b){a.x *= b.x; a.y *= b.y; }

    template<class T = float> vec2<T> operator+(vec2<T> a, T b){ return { a.x + b, a.y + b}; }
    template<class T = float> vec2<T> operator-(vec2<T> a, T b){ return { a.x - b, a.y - b}; }
    template<class T = float> vec2<T> operator/(vec2<T> a, T b){ return { a.x / b, a.y / b}; }
    template<class T = float> vec2<T> operator*(vec2<T> a, T b){ return { a.x * b, a.y * b}; }

    template<class T = float> vec2<T> operator+(T b, vec2<T> a){ return { b + a.x, b + a.y}; }
    template<class T = float> vec2<T> operator-(T b, vec2<T> a){ return { b - a.x, b - a.y}; }
    template<class T = float> vec2<T> operator/(T b, vec2<T> a){ return { b / a.x, b / a.y}; }
    template<class T = float> vec2<T> operator*(T b, vec2<T> a){ return { b * a.x, b * a.y}; }

    template<class T = float> void operator+=(vec2<T> &a, T b){a.x += b; a.y += b; }
    template<class T = float> void operator-=(vec2<T> &a, T b){a.x -= b; a.y -= b; }
    template<class T = float> void operator/=(vec2<T> &a, T b){a.x /= b; a.y /= b; }
    template<class T = float> void operator*=(vec2<T> &a, T b){a.x *= b; a.y *= b; }

    template<class T = float> bool operator==(vec2<T> a, vec2<T> b){ return a.x == b.x && a.y == b.y; }
    template<class T = float> bool operator>(vec2<T> a, vec2<T> b){ return a.x > b.x && a.y > b.y;}
    template<class T = float> bool operator<(vec2<T> a, vec2<T> b){ return a.x < b.x && a.y < b.y;}
    template<class T = float> bool operator!=(vec2<T> a, vec2<T> b){ return !(a==b);} 
    template<class T = float> bool operator==(vec2<T> a, T b){ return a.x == b && a.y == b; }
    template<class T = float> bool operator!=(vec2<T> a, T b){ return !(a == b); }
    
    template<class T = float> vec2<T> operator-(vec2<T> a){ return {-a.x, -a.y}; }
}

#define vec2i vec2<int>
#define vec2f vec2<float>
#define vec2d vec2<double>