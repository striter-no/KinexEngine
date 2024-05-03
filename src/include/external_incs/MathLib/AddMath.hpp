#pragma once

#include <algorithm>
#include <vector>
#include <sstream>
#include <string>
#include <bigint>
#include "math.h"

namespace adm{
    float clamp(float a, float b, float v){return std::min(std::max(v, a), b);}
    float sign(float a) { return (0 < a) - (a < 0); }
    float step(float edge, float x) { return x > edge; }
    float lerp(float a, float b, float f){return a + f * (b - a);}
    float aproximate_to_zero(float n, float speed, float border = 0.1){if(n<-border){n+=speed; } else if(n>border){n-=speed; } else if(n<=border && n >= -border){n=0;}}
    
    template<class T>
    long getmax(){
        return std::numeric_limits<T>::max();
    }

    template<typename T>
    T min(T v) {
        return v;
    }

    template<typename T, typename... Args>
    T min(T first, Args... args) {
        return std::min(first, min(args...));
    }

    template<class T>
    std::vector<T> operator+(std::vector<T> a, std::vector<T> b){
        std::vector<T> out; for(int i = 0; i < a.size(); i++){
            out.push_back(a[i]+b[i]);
        }

        return {out};
    }

    template<class T>
    std::vector<T> operator-(std::vector<T> a, std::vector<T> b){
        std::vector<T> out; for(int i = 0; i < a.size(); i++){
            out.push_back(a[i]-b[i]);
        }

        return {out};
    }

    template<class T>
    std::vector<T> operator*(std::vector<T> a, std::vector<T> b){
        std::vector<T> out; for(int i = 0; i < a.size(); i++){
            out.push_back(a[i]*b[i]);
        }

        return {out};
    }

    template<class T>
    std::vector<T> operator/(std::vector<T> a, std::vector<T> b){
        std::vector<T> out; for(int i = 0; i < a.size(); i++){
            out.push_back(a[i]/b);
        }

        return {out};
    }

    template<class T>
    std::vector<T> operator+(std::vector<T> a, T b){
        std::vector<T> out; for(int i = 0; i < a.size(); i++){
            out.push_back(a[i]+b);
        }

        return {out};
    }

    template<class T>
    std::vector<T> operator-(std::vector<T> a, T b){
        std::vector<T> out; for(int i = 0; i < a.size(); i++){
            out.push_back(a[i]-b);
        }

        return {out};
    }

    template<class T>
    std::vector<T> operator*(std::vector<T> a, T b){
        std::vector<T> out; for(int i = 0; i < a.size(); i++){
            out.push_back(a[i]*b);
        }

        return {out};
    }

    template<class T>
    std::vector<T> operator/(std::vector<T> a, T b){
        std::vector<T> out; for(int i = 0; i < a.size(); i++){
            out.push_back(a[i]/b);
        }

        return {out};
    }

    template<class T>
    std::vector<T> getDivisors(T num){
        std::vector<T> divisors;
        for(T i = 1; i < num; i++){
            if(num % i == 0){
                divisors.push_back(i);
            }
        }
        return {divisors};
    }

    template<class T>
    T varg(std::vector<T> vc){
        T vesum = (T)0; for(T&el:vc){vesum += el;}
        return vesum/((T)vc.size());
    }

    template<class T = float>
    T sqr(T x){
        return x*x;
    }

    template<class T = float>
    std::vector<T> vsqr(std::vector<T> vc){
        std::vector<T> o; for(const T&el:vc){
            o.push_back(sqr(el));
        }
        return {o};
    }

    std::vector<int> factorize(int n) {
        std::vector<int> factors;
        
        for (int i = 2; i <= n; i++) {
            while (n % i == 0) {
                factors.push_back(i);
                n /= i;
            }
        }
        
        return factors;
    }

    template<class T>
    std::vector<T> vecclamp(std::vector<T> vc, T minv, T maxv){
        std::vector<T> out;
        for(int i = 0; i < vc.size(); i++){
            out.push_back(std::min(maxv, std::max(minv, vc[i])));
        }
        return {out};
    }

    float rad(float angle){
        return angle * (3.14159265358979323846 / 180);
    }

    float deg(float rads){
        return rads *  (180 / 3.14159265358979323846);
    }

    std::string dec2hex(bigint num) {
        std::stringstream ss;
        while(num!=0) {
            bigint temp  = 0;
            temp = num % to_bigint(16);
            if(temp < 10) {
                ss << (char)(std::stoi(temp.getString()) + 48);
            } else {
                ss << (char)(std::stoi(temp.getString()) + 87 - 32);
            }
            num = num/16;
        }
        std::string result = ss.str();
        std::reverse(result.begin(), result.end());
        return result;
    }
}