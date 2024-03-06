#pragma once

#include "pvector.hpp"
#include "Vector4.hpp"
#include "AddMath.hpp"
#include <map>

typedef std::pair<eml::vec2f, eml::vec2f> rectf_t;
typedef std::pair<eml::vec2d, eml::vec2d> rectd_t;
typedef std::pair<eml::vec2i, eml::vec2i> recti_t;

float dot(eml::vec2f a, eml::vec2f b){ return a.x * b.x + a.y * b.y; }
float dot(eml::vec3f a, eml::vec3f b){ return a.x * b.x + a.y * b.y + a.z * b.z; }
float dist(eml::vec3f a, eml::vec3f b){ return sqrtf(pow(b.x - a.x, 2) + pow(b.y - a.y, 2) + pow(b.z - a.z, 2)); }
float len(eml::vec3f v) { return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z); }

float dot(eml::vec4f a, eml::vec4f b){ return a.x * b.x + a.y * b.y + a.z * b.z; }
float dist(eml::vec4f a, eml::vec4f b){ return sqrtf(pow(b.x - a.x, 2) + pow(b.y - a.y, 2) + pow(b.z - a.z, 2)); }
float len(eml::vec4f v) { return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z); }

float len(eml::vec2f v) { return sqrtf(v.x * v.x + v.y * v.y); }
float dist(eml::vec2f a, eml::vec2f b){ return sqrtf(pow(b.x - a.x, 2) + pow(b.y - a.y, 2)); }

// Функция возвращает углы (радианы) между центральной точкой и данной точкой
float angle(eml::vec2f point, eml::vec2f center = {0.f, 0.f}){
    return atan2f(point.y - center.y, point.x - center.x);
}

// Функция возвращает нормализованый вектор направления по углу (радианы)
eml::vec2f directionByAngle(float radians){
    return {cosf(radians), sinf(radians)};
}

eml::vec2f vec2i_tf(eml::vec2i v){return {v.x, v.y};};
eml::vec3f vec3i_tf(eml::vec3i v){return {v.x, v.y, v.z};};
eml::vec4f vec4i_tf(eml::vec4i v){return {v.x, v.y, v.z, v.w};};

eml::vec2i vec2f_ti(eml::vec2f v){return {round(v.x), round(v.y)};};
eml::vec3i vec3f_ti(eml::vec3f v){return {round(v.x), round(v.y), round(v.z)};};
eml::vec4i vec4f_ti(eml::vec4f v){return {round(v.x), round(v.y), round(v.z), round(v.w)};};

eml::vec3f abs(eml::vec3f v){ return {std::abs(v.x), std::abs(v.y), std::abs(v.z)};}
eml::vec3f norm(eml::vec3f a){ return (len(a) != 0) ? (a / len(a)) : (eml::vec3f(0, 0, 0)); }
eml::vec3f clamp(float a, float b, eml::vec3f v){ return {adm::clamp(a, b, v.x), adm::clamp(a, b, v.y), adm::clamp(a, b, v.z)}; }
eml::vec3f cross(eml::vec3f a, eml::vec3f b){ return { a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x }; }
eml::vec3f lerp(eml::vec3f a, eml::vec3f b, eml::vec3f f){ return {adm::lerp(a.x, b.x, f.x), adm::lerp(a.y, b.y, f.y), adm::lerp(a.z, b.z, f.z)};}
eml::vec3f sign(eml::vec3f const& v) { return eml::vec3f(adm::sign(v.x), adm::sign(v.y), adm::sign(v.z)); }
eml::vec3f step(eml::vec3f const& edge, eml::vec3f v) { return eml::vec3f(adm::step(edge.x, v.x), adm::step(edge.y, v.y), adm::step(edge.z, v.z)); }
eml::vec3f reflect(eml::vec3f v, eml::vec3f normal){ return v - 2 * dot(v, normal) * normal; }
eml::vec2f reflect(eml::vec2f v, eml::vec2f normal){ return v - 2 * dot(v, normal) * normal; }

eml::vec4f abs(eml::vec4f v){ return {std::abs(v.x), std::abs(v.y), std::abs(v.z)};}
eml::vec4f norm(eml::vec4f a){ return len(a) != 0 ? a / len(a): eml::vec4f(0, 0, 0); }
eml::vec4f clamp(float a, float b, eml::vec4f v){ return {adm::clamp(a, b, v.x), adm::clamp(a, b, v.y), adm::clamp(a, b, v.z)}; }
eml::vec4f cross(eml::vec4f a, eml::vec4f b){ return { a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x }; }
eml::vec4f lerp(eml::vec4f a, eml::vec4f b, eml::vec4f f){ return {adm::lerp(a.x, b.x, f.x), adm::lerp(a.y, b.y, f.y), adm::lerp(a.z, b.z, f.z)};}
eml::vec4f sign(eml::vec4f const& v) { return eml::vec4f(adm::sign(v.x), adm::sign(v.y), adm::sign(v.z)); }
eml::vec4f step(eml::vec4f const& edge, eml::vec4f v) { return eml::vec3f(adm::step(edge.x, v.x), adm::step(edge.y, v.y), adm::step(edge.z, v.z)); }

eml::vec2f abs(eml::vec2f v){ return {std::abs(v.x), std::abs(v.y)};}
eml::vec2f norm(eml::vec2f a){ return len(a) != 0 ? a / len(a): eml::vec2f(0, 0); }
eml::vec2f clamp(float a, float b, eml::vec2f v){ return {adm::clamp(a, b, v.x), adm::clamp(a, b, v.y)}; }
eml::vec2f cross(eml::vec2f a, eml::vec2f b){ return a.x * b.y - a.y * b.x; }
eml::vec2f lerp(eml::vec2f a, eml::vec2f b, eml::vec2f f){ return {adm::lerp(a.x, b.x, f.x), adm::lerp(a.y, b.y, f.y)};}

eml::vec3f normal(eml::vec3f a, eml::vec3f b, eml::vec3f c){eml::vec3f edge1 = b - a; eml::vec3f edge2 = c - a; return cross(edge1, edge2); }
eml::vec2f normal(eml::vec2f a, eml::vec2f b, eml::vec2f c){eml::vec2f edge1 = b - a; eml::vec2f edge2 = c - a; return cross(edge1, edge2); }
eml::vec4f normal(eml::vec4f a, eml::vec4f b, eml::vec4f c){eml::vec4f edge1 = b - a; eml::vec4f edge2 = c - a; return cross(edge1, edge2); }

eml::vec2i round(eml::vec2f v){return {round(v.x), round(v.y)};}
eml::vec3i round(eml::vec3f v){return {round(v.x), round(v.y), round(v.z)};}
eml::vec4i round(eml::vec4f v){return {round(v.x), round(v.y), round(v.z), round(v.w)};}

eml::vec2i round(eml::vec2d v){return {round(v.x), round(v.y)};}
eml::vec3i round(eml::vec3d v){return {round(v.x), round(v.y), round(v.z)};}
eml::vec4i round(eml::vec4d v){return {round(v.x), round(v.y), round(v.z), round(v.w)};}

eml::vec2f rad(eml::vec2f v){return {adm::rad(v.x), adm::rad(v.y)};}
eml::vec3f rad(eml::vec3f v){return {adm::rad(v.x), adm::rad(v.y), adm::rad(v.z)};}
eml::vec4f rad(eml::vec4f v){return {adm::rad(v.x), adm::rad(v.y), adm::rad(v.z), adm::rad(v.w)};}

eml::vec2d rad(eml::vec2d v){return {adm::rad(v.x), adm::rad(v.y)};}
eml::vec3d rad(eml::vec3d v){return {adm::rad(v.x), adm::rad(v.y), adm::rad(v.z)};}
eml::vec4d rad(eml::vec4d v){return {adm::rad(v.x), adm::rad(v.y), adm::rad(v.z), adm::rad(v.w)};}

bool isRectIntersect(
    rectf_t r1, rectf_t r2
){
    return (r1.first.x < (r2.first.x + r2.second.x)) && 
           ((r1.first.x + r1.second.x) > r2.first.x) &&
           (r1.first.y < (r2.first.y + r2.second.y)) &&
           ((r1.first.y + r1.second.y) > r2.first.y);
}

bool isPointInRect(eml::vec2f point, rectf_t rect){
    return (point.x >= rect.first.x) && (point.x <= rect.first.x + rect.second.x) &&
           (point.y >= rect.first.y) && (point.y <= rect.first.y + rect.second.y);
}

bool isPointInsideQuadrilateral(eml::vec2f point, eml::vec2f p0, eml::vec2f p1, eml::vec2f p2, eml::vec2f p3) {
    eml::vec2f edge0 = p1 - p0;
    eml::vec2f edge1 = p2 - p1;
    eml::vec2f edge2 = p3 - p2;
    eml::vec2f edge3 = p0 - p3;

    eml::vec2f toPoint0 = point - p0;
    eml::vec2f toPoint1 = point - p1;
    eml::vec2f toPoint2 = point - p2;
    eml::vec2f toPoint3 = point - p3;

    bool side0 = (toPoint0.x * edge0.y - toPoint0.y * edge0.x) <= 0;
    bool side1 = (toPoint1.x * edge1.y - toPoint1.y * edge1.x) <= 0;
    bool side2 = (toPoint2.x * edge2.y - toPoint2.y * edge2.x) <= 0;
    bool side3 = (toPoint3.x * edge3.y - toPoint3.y * edge3.x) <= 0;

    return (side0 == side1) && (side1 == side2) && (side2 == side3);
}

bool isSegmentIntersectingQuadrilateral(eml::vec2f p0, eml::vec2f p1, eml::vec2f q0, eml::vec2f q1, eml::vec2f q2, eml::vec2f q3) {
    // Функция для определения ориентации трех точек
    auto orientation = [](eml::vec2f p, eml::vec2f q, eml::vec2f r) -> int {
        float val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
        if (val == 0) return 0;  // Коллинеарны
        return (val > 0) ? 1 : 2; // Для определения направления поворота
    };

    // Функция для проверки, лежит ли точка q на отрезке pr
    auto onSegment = [](eml::vec2f p, eml::vec2f q, eml::vec2f r) -> bool {
        if (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
            q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y))
            return true;
        return false;
    };

    // Функция для определения пересечения двух отрезков
    auto doIntersect = [&](eml::vec2f p0, eml::vec2f q0, eml::vec2f p1, eml::vec2f q1) -> bool {
        int o1 = orientation(p0, q0, p1);
        int o2 = orientation(p0, q0, q1);
        int o3 = orientation(p1, q1, p0);
        int o4 = orientation(p1, q1, q0);

        if (o1 != o2 && o3 != o4) return true;
        if (o1 == 0 && onSegment(p0, p1, q0)) return true;
        if (o2 == 0 && onSegment(p0, q1, q0)) return true;
        if (o3 == 0 && onSegment(p1, p0, q1)) return true;
        if (o4 == 0 && onSegment(p1, q0, q1)) return true;

        return false;
    };


    // Проверка для каждой стороны квадрата
    return doIntersect(p0, p1, q0, q1) || doIntersect(p0, p1, q1, q2) ||
           doIntersect(p0, p1, q2, q3) || doIntersect(p0, p1, q3, q0);
}

// Использование функции
bool isSegmentInsideQuadrilateral(eml::vec2f p0, eml::vec2f p1, eml::vec2f q0, eml::vec2f q1, eml::vec2f q2, eml::vec2f q3) {
    // Проверяем, что начальная и конечная точки отрезка не лежат вне квадрата
    if (!isPointInsideQuadrilateral(p0, q0, q1, q2, q3) || !isPointInsideQuadrilateral(p1, q0, q1, q2, q3))
        return false;

    // Проверяем, пересекается ли отрезок с каждой стороной квадрата
    return !isSegmentIntersectingQuadrilateral(p0, p1, q0, q1, q2, q3);
}


bool getInterPoint(eml::pvector a, eml::pvector b, eml::vec2f& intersectionPoint) {
    float A1 = a.y2 - a.y1;
    float B1 = a.x1 - a.x2;
    float C1 = A1 * a.x1 + B1 * a.y1;

    float A2 = b.y2 - b.y1;
    float B2 = b.x1 - b.x2;
    float C2 = A2 * b.x1 + B2 * b.y1;

    float det = A1 * B2 - A2 * B1;
    if (det == 0) {
        return false; // Отрезки параллельны
    } else {
        intersectionPoint.x = (B2 * C1 - B1 * C2) / det;
        intersectionPoint.y = (A1 * C2 - A2 * C1) / det;

        // Проверка, что точка пересечения лежит внутри обоих отрезков
        float t1 = (a.x2 - a.x1) != 0 ? (intersectionPoint.x - a.x1) / (a.x2 - a.x1) : 0.5;
        float t2 = (b.x2 - b.x1) != 0 ? (intersectionPoint.x - b.x1) / (b.x2 - b.x1) : 0.5;

        float u1 = (a.y2 - a.y1) != 0 ? (intersectionPoint.y - a.y1) / (a.y2 - a.y1) : 0.5;
        float u2 = (b.y2 - b.y1) != 0 ? (intersectionPoint.y - b.y1) / (b.y2 - b.y1) : 0.5;

        if (t1 >= 0 && t1 <= 1 && t2 >= 0 && t2 <= 1 && u1 >= 0 && u1 <= 1 && u2 >= 0 && u2 <= 1) {
            return true;
        } else {
            return false;
        }
    }
}

bool isPointOnVector(eml::pvector a, eml::vec2f point) {
    float t = (a.x2 - a.x1) != 0 ? (point.x - a.x1) / (a.x2 - a.x1) : 0.5;
    float u = (a.y2 - a.y1) != 0 ? (point.y - a.y1) / (a.y2 - a.y1) : 0.5;

    return (t >= 0 && t <= 1 && u >= 0 && u <= 1);
}

bool isIntersected(eml::pvector a, eml::pvector b){
    eml::vec2f intersectionPoint;

    float A1 = a.y2 - a.y1;
    float B1 = a.x1 - a.x2;
    float C1 = A1 * a.x1 + B1 * a.y1;

    float A2 = b.y2 - b.y1;
    float B2 = b.x1 - b.x2;
    float C2 = A2 * b.x1 + B2 * b.y1;

    float det = A1 * B2 - A2 * B1;
    if (det == 0) {
        return false; // Отрезки параллельны
    } else {
        intersectionPoint.x = (B2 * C1 - B1 * C2) / det;
        intersectionPoint.y = (A1 * C2 - A2 * C1) / det;

        // Проверка, что точка пересечения лежит внутри обоих отрезков
        float t1 = (a.x2 - a.x1) != 0 ? (intersectionPoint.x - a.x1) / (a.x2 - a.x1) : 0.5;
        float t2 = (b.x2 - b.x1) != 0 ? (intersectionPoint.x - b.x1) / (b.x2 - b.x1) : 0.5;

        float u1 = (a.y2 - a.y1) != 0 ? (intersectionPoint.y - a.y1) / (a.y2 - a.y1) : 0.5;
        float u2 = (b.y2 - b.y1) != 0 ? (intersectionPoint.y - b.y1) / (b.y2 - b.y1) : 0.5;

        if (t1 >= 0 && t1 <= 1 && t2 >= 0 && t2 <= 1 && u1 >= 0 && u1 <= 1 && u2 >= 0 && u2 <= 1) {
            return true;
        } else {
            return false;
        }
    }
}

int orientation(eml::vec2f p, eml::vec2f q, eml::vec2f r) {
    float val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;  // Коллинеарны
    return (val > 0) ? 1 : 2; // Для определения направления поворота
}

// Функция для проверки, лежит ли точка q на отрезке pr
bool onSegment(eml::vec2f p, eml::vec2f q, eml::vec2f r) {
    if (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
        q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y))
        return true;
    return false;
}

// Функция для определения, пересекаются ли два отрезка
bool doIntersect(eml::vec2f p1, eml::vec2f q1, eml::vec2f p2, eml::vec2f q2) {
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    if (o1 != o2 && o3 != o4) return true;
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    return false;
}

bool findIntersection(eml::vec2f p1, eml::vec2f q1, eml::vec2f p2, eml::vec2f q2, eml::vec2f &interpoint) {
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    if (o1 != o2 && o3 != o4) {
        // Отрезки пересекаются, находим точку пересечения
        float x1 = p1.x, y1 = p1.y;
        float x2 = q1.x, y2 = q1.y;
        float x3 = p2.x, y3 = p2.y;
        float x4 = q2.x, y4 = q2.y;

        float determinant = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
        if (determinant != 0) {
            float intersectionX = ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4)) / determinant;
            float intersectionY = ((x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4)) / determinant;

            interpoint = {intersectionX, intersectionY};
            return true; 
        }
    }

    // Отрезки не пересекаются, возвращаем нулевой вектор
    return false;
}

bool isSegmentIntersectsQuad(eml::pvector pa, eml::vec2f p0, eml::vec2f p1, eml::vec2f p2, eml::vec2f p3, eml::vec2f &interPoint, eml::pvector &intersectedSegment) {
    eml::pvector edge0(p0, p1);
    eml::pvector edge1(p1, p2);
    eml::pvector edge2(p2, p3);
    eml::pvector edge3(p3, p0);

    array<eml::pvector, 4> edges{{
        {p0, p1}, {p1, p2}, {p2, p3}, {p3, p0}
    }};

    sort(edges.begin(), edges.end(), 
        [&](eml::pvector &a, eml::pvector &b){
            return dist(a.getCenter(), pa.getCenter()) < dist(b.getCenter(), pa.getCenter());
        });

    
    for(eml::pvector &edge: edges){
        if(findIntersection(pa.getPointA(), pa.getPointB(), edge.getPointA(), edge.getPointB(), interPoint)){
            intersectedSegment = edge;
            return true;
        }
    }

    return false;
}