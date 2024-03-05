#pragma once

#include "VectorFuncs.hpp"
#include <vector>

#include <algorithm>
#include <cmath>
using namespace std;

struct RGB {
    float r; // [0, 1]
    float g; // [0, 1]
    float b; // [0, 1]
};

struct HSL {
    float h; // [0, 360]
    float s; // [0, 1]
    float l; // [0, 1]
};

RGB v32rgb(eml::vec3f rgb){
    return {rgb.x / 255.f, rgb.y / 255.f, rgb.z / 255.f};
}

HSL v32hsl(eml::vec3f hsl){
    return {(int)hsl.x % 360, hsl.y / 255.f, hsl.z / 255.f};
}

eml::vec3f hsl2v3(HSL hsl){
    return {hsl.h, hsl.s, hsl.l};
}

eml::vec3f rgb2v3(RGB rgb){
    return {rgb.r, rgb.g, rgb.b};
}

HSL RGBtoHSL(RGB rgb) {
    float max = std::max(rgb.r, std::max(rgb.g, rgb.b));
    float min = std::min(rgb.r, std::min(rgb.g, rgb.b));

    float h, s, l;
    l = (max + min) / 2.0;

    if(max == min) {
        h = s = 0; // achromatic
    } else {
        float d = max - min;
        s = l > 0.5 ? d / (2.0 - max - min) : d / (max + min);

        if(max == rgb.r) {
            h = (rgb.g - rgb.b) / d + (rgb.g < rgb.b ? 6.0 : 0.0);
        } else if(max == rgb.g) {
            h = (rgb.b - rgb.r) / d + 2.0;
        } else {
            h = (rgb.r - rgb.g) / d + 4.0;
        }

        h /= 6.0;
    }

    return HSL{h * 360, s, l};
}

RGB HSLtoRGB(HSL hsl) {
    float r, g, b;

    if(hsl.s == 0) {
        r = g = b = hsl.l; // achromatic
    } else {
        auto hue2rgb = [&](float p, float q, float t) {
            if(t < 0) t += 1;
            if(t > 1) t -= 1;
            if(t < 1.0/6.0) return p + (q - p) * 6.f * t;
            if(t < 1.0/2.0) return q;
            if(t < 2.0/3.0) return p + (q - p) * (2.f/3.f - t) * 6.f;
            return p;
        };

        float q = hsl.l < 0.5f ? hsl.l * (1 + hsl.s) : hsl.l + hsl.s - hsl.l * hsl.s;
        float p = 2 * hsl.l - q;
        float h = hsl.h / 360;
        r = hue2rgb(p, q, h + 1.f/3.f);
        g = hue2rgb(p, q, h);
        b = hue2rgb(p, q, h - 1.f/3.f);
    }

    return RGB{r, g, b};
}

vector<eml::vec3f> hslPalitra(eml::vec3f stColor, int clrNum){
    vector<eml::vec3f> o;
    for(int i = 0; i < clrNum; i++){
        o.push_back(rgb2v3(HSLtoRGB({
            (float)((((int)stColor.x) + (i * (360/clrNum))) % 360),
            (float)((stColor.y) / 255.f),
            (float)(stColor.z / 255.f)
        })) * 255.f);
    }
    return o;
}

eml::vec3f rgbToHsv(RGB rgb) {
    float maxVal = std::max(rgb.r, std::max(rgb.g, rgb.b));
    float minVal = std::min(rgb.r, std::min(rgb.g, rgb.b));
    float delta = maxVal - minVal;

    float h, s, v;
    v = maxVal;

    if (maxVal != 0) {
        s = delta / maxVal;
    } else {
        s = 0;
        h = -1;
        return eml::vec3f(h, s, v);
    }

    if (rgb.r == maxVal) {
        h = (rgb.g - rgb.b) / delta;
    } else if (rgb.g == maxVal) {
        h = 2 + (rgb.b - rgb.r) / delta;
    } else {
        h = 4 + (rgb.r - rgb.g) / delta;
    }

    h *= 60;
    if (h < 0) {
        h += 360;
    }

    return eml::vec3f(h, s, v);
}

// Функция для конвертации HSV в RGB
eml::vec3f hsvToRgb(eml::vec3f hsv) {
    float c = hsv.y * hsv.z;
    float x = c * (1 - std::abs(std::fmod(hsv.x / 60, 2) - 1));
    float m = hsv.z - c;

    float r, g, b;
    hsv.x = (int)hsv.x % 360;
    if (hsv.x >= 0 && hsv.x < 60) {
        r = c;
        g = x;
        b = 0;
    } else if (hsv.x >= 60 && hsv.x < 120) {
        r = x;
        g = c;
        b = 0;
    } else if (hsv.x >= 120 && hsv.x < 180) {
        r = 0;
        g = c;
        b = x;
    } else if (hsv.x >= 180 && hsv.x < 240) {
        r = 0;
        g = x;
        b = c;
    } else if (hsv.x >= 240 && hsv.x < 300) {
        r = x;
        g = 0;
        b = c;
    } else {
        r = c;
        g = 0;
        b = x;
    }

    return eml::vec3f(r + m, g + m, b + m);
}

eml::vec3f gradient(eml::vec3f s, eml::vec3f e, float f){
    return {
        adm::lerp(s.x, e.x, f),
        adm::lerp(s.y, e.y, f),
        adm::lerp(s.z, e.z, f)
    };
}

eml::vec4f gradient(eml::vec4f s, eml::vec4f e, float f){
    return {
        adm::lerp(s.x, e.x, f),
        adm::lerp(s.y, e.y, f),
        adm::lerp(s.z, e.z, f),
        adm::lerp(s.w, e.w, f)
    };
}