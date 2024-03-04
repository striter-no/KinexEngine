#pragma once 
#include <Kinex/init.hpp>
#include <Kinex/internal.hpp>
#include "Camera.hpp"
#include "Input.hpp"
#include "Physics.hpp"

namespace knx{
    class FPController{
        irl::RigidBody rigidBody;
        string rigidBodyName;

        Camera *camera;
        
        bool canFly = false;
        float jumpStrength = 1;
        public:

        Camera *getCamera(){return camera;}
        irl::RigidBody &getRigidBody(){return rigidBody;}
        const float &getJumpStrength(){return jumpStrength;}
        const bool &getFlyMode(){return canFly;}

        void setCamera(Camera *camera){this->camera = camera;}
        void setJumpStrength(int val){jumpStrength = val;}
        void setFlyMode(bool mode){canFly = mode;}

        void update(Input &input, PhysicsScene &scene){
            camera->rotate(input.getCursorAxisX(true), input.getCursorAxisY(true));

            vec3f front = camera->getTransform().getFront();
            vec3f right = camera->getTransform().getRight();

            if(!canFly){
                front.y = 0;
                right.y = 0;
            }

            rigidBody.addVelocity(input.getAxisX() * right);
            rigidBody.addVelocity(input.getAxisZ() * front);
            if(canFly) rigidBody.addVelocity(input.getAxisY() * camera->getTransform().getUp());
            
            if(!input.isKeyPressed(GLFW_KEY_SPACE)) return;

            // Если нажат пробел
            auto collInfo = scene.getAllCollisionWithRigidBody(rigidBodyName);
            for(auto &coll: collInfo){
                if(coll.getNormal() != vec3f{0, 1, 0}) continue;
                // Если объект столкнулся снизу
                rigidBody.addVelocity(camera->getTransform().getUp() * jumpStrength);
            }

            camera->getTransform() = rigidBody.getTransform();
        }

        FPController(irl::Transform transform, Camera *camera, string name = "__FPC_Controller__"){
            ;
        }

        FPController(){}
        ~FPController(){}
    };
};