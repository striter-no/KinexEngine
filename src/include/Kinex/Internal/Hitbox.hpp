#pragma once
#include <Kinex/init.hpp>
#include "Mesh.hpp"

namespace knx{
    namespace irl{
        class Hitbox{
            vec3f dotMin, dotMax;
            vec3f lowerCentrP, upperCentrP,
                  frontCentrP, backwardCentrP,
                  rightCentrP, leftCentrP;
            
            bool interLines( float min1, float max1, float min2, float max2 ){
                if (min1 > max2) return false;
                if (max1 < min2) return false;
                return true;
            }

            public:

            const vec3f &getDotMin(){return dotMin;}
            const vec3f &getDotMax(){return dotMax;}
            const vec3f &getLowerCenter(){return lowerCentrP;}
            const vec3f &getUpperCenter(){return upperCentrP;}
            const vec3f &getFrontCenter(){return frontCentrP;}
            const vec3f &getBackwardCenter(){return backwardCentrP;}
            const vec3f &getRightCenter(){return rightCentrP;}
            const vec3f &getLeftCenter(){return leftCentrP;}

            void move(const vec3f &vel){
                dotMin += vel;
                dotMax += vel;
                computePoints();
            }

            bool intersects(const Hitbox &other){
                for (int i = 0; i < 3; ++i){
                    if (!interLines((*this)[i], (*this)[i + 3], other[i], other[i + 3])) {
                        return false;
                    }
                }
                return true;
            }

            bool intersects(const Hitbox &other, vec3f &vnormal){
                vnormal = {0.f};
                for (int i = 0; i < 3; ++i){
                    if (!interLines((*this)[i], (*this)[i + 3], other[i], other[i + 3])) {
                        return false;
                    }
                }

                if ((*this)[3] == other[0] || (*this)[0] == other[3])
                    vnormal.x = ((*this)[3] == other[0]) ? -1.0f : 1.0f;
                else if ((*this)[4] == other[1] || (*this)[1] == other[4])
                    vnormal.y = ((*this)[4] == other[1]) ? -1.0f : 1.0f;
                else if ((*this)[5] == other[2] || (*this)[2] == other[5])
                    vnormal.z = ((*this)[5] == other[2]) ? -1.0f : 1.0f;

                return true;
            }

            Hitbox(vec3f minPoint, vec3f maxPoint): dotMin(minPoint), dotMax(maxPoint) {
                computePoints();
            }

            Hitbox(Mesh mesh){
                dotMin = mesh[0]; dotMax = mesh[1];
                for(int i = 0; i < mesh.size(); i++){
                    if(mesh[i].x > dotMax.x) dotMax.x = mesh[i].x;
                    if(mesh[i].y > dotMax.y) dotMax.y = mesh[i].y;
                    if(mesh[i].z > dotMax.z) dotMax.z = mesh[i].z;

                    if(mesh[i].x < dotMin.x) dotMin.x = mesh[i].x;
                    if(mesh[i].y < dotMin.y) dotMin.y = mesh[i].y;
                    if(mesh[i].z < dotMin.z) dotMin.z = mesh[i].z;
                }

                computePoints();
            }

            void computePoints(){
                float xEdge = dotMax.x - dotMin.x, 
                      yEdge = dotMax.y - dotMin.y, 
                      zEdge = dotMax.z - dotMin.z;

                leftCentrP     = vec3f(0, yEdge/2, zEdge/2);
                rightCentrP    = vec3f(xEdge, yEdge/2, zEdge/2);

                lowerCentrP    = vec3f(xEdge/2, 0, zEdge/2);
                upperCentrP    = vec3f(xEdge/2, yEdge, zEdge/2);

                frontCentrP    = vec3f(xEdge/2, yEdge/2, 0);
                backwardCentrP = vec3f(xEdge/2, yEdge/2, zEdge);
            }

            Hitbox(){}
            ~Hitbox(){}

            float &operator[](int inx){
                switch(inx){
                    case 0: return dotMin.x;
                    case 1: return dotMin.y;
                    case 2: return dotMin.z;
                    case 3: return dotMax.x;
                    case 4: return dotMax.y;
                    case 5: return dotMax.z;
                }
            }

            const float &operator[](int inx) const{
                switch(inx){
                    case 0: return dotMin.x;
                    case 1: return dotMin.y;
                    case 2: return dotMin.z;
                    case 3: return dotMax.x;
                    case 4: return dotMax.y;
                    case 5: return dotMax.z;
                }
            }
        };
    };
};