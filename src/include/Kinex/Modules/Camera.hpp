#pragma once
#include <Kinex/init.hpp>
#include <Kinex/internal.hpp>

namespace knx{
    class Camera{
        irl::Transform transform;
        float speed; 
        float sensivity;
        
        glm::mat4x4 projection;
        float fov = -1, initFov = -1;
        float near_ = -1, far_ = -1, aspect = -1;

        public:

        const float &getSpeed(){return speed;} 
        const float &getSensivity(){return sensivity;}
        const float &getFov(){return fov;}
        const float &getInitFov(){return initFov;}
        const float &getNear(){return near_;}
        const float &getFar(){return far_;}
        const float &getAspect(){return aspect;}
        const float getZoom(){ return fov - initFov; }

        irl::Transform &getTransform(){ return transform; }
        const glm::mat4x4 &getProj(){ return projection; }

        void setFov(const float &val){fov = val;}
        void setSpeed(const float &val){speed = val;}
        void setSensivity(const float &val){sensivity = val;}

        void setProjection(vec2i res, float _near, float _far){
            aspect = (float)res.x / (float)res.y; near_ = _near; far_ = _far;
            projection = glm::perspective(fov, aspect, near_, far_);
        }

        void rotate(float rotX, float rotY, bool constrPitch = true){
            rotX *= sensivity; transform.getRotation().x += rotX;
            rotY *= sensivity; transform.getRotation().y += rotY;

            // cout<<"rotate: "<<transform.getRotation().str()<<endl;

            if (constrPitch){
                if (transform.getRotation().x > 89.0f)  transform.getRotation().x = 89.0f;
                if (transform.getRotation().x < -89.0f) transform.getRotation().x = -89.0f;
            }
        }

        void move(vec3i val, float deltaTime = 1){
            float velocity = speed * deltaTime;

            switch(val.x){
                case -1: transform.getPosition() -= transform.getRight() * velocity;
                case  1: transform.getPosition() += transform.getRight() * velocity;
            }

            switch(val.z){
                case -1: transform.getPosition() -= transform.getFront() * velocity;
                case  1: transform.getPosition() += transform.getFront() * velocity;
            }

            switch(val.y){
                case -1: transform.getPosition() -= transform.getUp() * velocity;
                case  1: transform.getPosition() += transform.getUp() * velocity;
            }

            cout<<"moved: "<<transform.getPosition().str()<<endl;
        }

        Camera(irl::Transform transform, float speed, float sensivity):
               transform(transform), speed(speed), sensivity(sensivity){
            ;
        }

        Camera(){}
        ~Camera(){}
    };
};