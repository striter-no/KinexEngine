#pragma once
#include <Kinex/init.hpp>
#include "Hitbox.hpp"


namespace knx{
    namespace irl{

        class Collision{
            bool  collided = false;
            vec3f normal = {0.f};

            vec3f velocity = {0.f};
            vec3f velocitySubject = {0.f};

            vec3f direction = {0.f};
            vec3f directionSubject = {0.f};

            Hitbox firstCollided;
            Hitbox collisionSubject;
            
            public:

            const bool &getCollidedStatus(){return collided; }
            const vec3f &getNormal(){return normal; }
            const vec3f &getVelocity(){return velocity; }
            const vec3f &getVelocitySubject(){return velocitySubject; }
            const vec3f &getDirection(){return direction; }
            const vec3f &getDirectionSubject(){return directionSubject; }

            const Hitbox &getCollidedObject(){return firstCollided; }
            const Hitbox &getCollisionSubject(){return collisionSubject; }

            static Collision NOT_COLLIDED(){return irl::Collision(false, {-1}, {-1}, {-1}, {-1}, {-1}, {{-1}, {-1}}, {{-1}, {-1}});}

            Collision(
                bool  collided,
                vec3f normal,
                vec3f velocity,
                vec3f velocitySubject,
                vec3f direction,
                vec3f directionSubject,
                Hitbox firstCollided,
                Hitbox collisionSubject
            ): collided(collided),
               normal(normal),
               velocity(velocity),
               velocitySubject(velocitySubject),
               direction(direction),
               directionSubject(directionSubject),
               firstCollided(firstCollided),
               collisionSubject(collisionSubject) {
                ;
            }

            Collision(){}
            ~Collision(){}
        };
    };
};