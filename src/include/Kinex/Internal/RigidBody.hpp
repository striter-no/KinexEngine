#pragma once
#include <Kinex/init.hpp>
#include "Hitbox.hpp"
#include "Collision.hpp"
#include "PhysicsMaterial.hpp"
#include "Transform.hpp"

namespace knx{
    namespace irl{
        float VELOCITY_TRESHOLD = 0;
        class RigidBody{
            PhysicsMaterial material;
            float mass = 0;
            vec3f velocity = 0;

            Hitbox hitbox;

            bool isTransparent = false;
            bool isStatic = false;
            
            Transform *transformPtr;
            public:

            Transform &getTransform(){
                return *transformPtr;
            }

            const vec3f &getPosition(){return transformPtr->getPosition();}
            const PhysicsMaterial &getMaterial(){return material;}
            const Hitbox &getHitbox(){return hitbox;}
            const vec3f &getDirection(){return transformPtr->getRotation();}
            const vec3f &getVelocity(){return velocity;}
            const float &getMass(){return mass;}

            void setMaterial(const PhysicsMaterial &material){this->material = material;}
            void setHitbox(const Hitbox &hitbox){this->hitbox = hitbox;}
            void setDirection(const vec3f &direction){transformPtr->getRotation() = direction;}
            void setVelocity(const vec3f &velocity){this->velocity = velocity;}
            void setPosition(const vec3f &pos){transformPtr->setPosition(pos);}
            void setMass(const float &mass){this->mass = mass;}

            void linkTransform(Transform *transform){transformPtr = transform;}

            void addVelocity(const vec3f &vel){
                velocity = vel;
            }

            const Collision processCollision(RigidBody &other){
                
                Hitbox localHitbox = hitbox;
                localHitbox.move((transformPtr->getPosition()) + (velocity * (1/mass) * transformPtr->getRotation()));
                Hitbox localOtherHitbox = other.hitbox;
                localOtherHitbox.move((other.transformPtr->getPosition()) + ((other.velocity * (1 / other.mass)) * other.transformPtr->getRotation()));
                
                vec3f vnormal;
                Collision collision(
                    localHitbox.intersects(localOtherHitbox, vnormal),
                    vnormal,
                    velocity * (1/mass),
                    (other.velocity * (1 / other.mass)),
                    norm(velocity * (1/mass)),
                    norm((other.velocity * (1 / other.mass))),
                    hitbox,
                    other.hitbox
                );

                if(collision.getCollidedStatus()){
                    
                    if((other.hitbox.getUpperCenter().y - hitbox.getLowerCenter().y) <= 0 || (hitbox.getLowerCenter().y - other.hitbox.getUpperCenter().y) <= 0) {
						velocity.y = 0;
					}
					if(abs(hitbox.getDotMin().y-other.hitbox.getDotMax().y) > 0.5){
						if(other.hitbox.getLeftCenter().x - hitbox.getRightCenter().x <= 0 || hitbox.getRightCenter().x - other.hitbox.getLeftCenter().x <= 0) 
							velocity.x = 0;
						if(other.hitbox.getFrontCenter().z - hitbox.getBackwardCenter().z <= 0 || hitbox.getBackwardCenter().z - other.hitbox.getFrontCenter().z <= 0) 
							velocity.z = 0;
					}

                    transformPtr->setPosition((transformPtr->getPosition()) / 
                        (((isStatic || velocity * (1/mass) == 0.f) ? material.StaticFriction : material.DynamicFriction) + 
                         ((other.isStatic || (other.velocity * (1 / other.mass)) == 0.f) ? other.material.StaticFriction : other.material.DynamicFriction)) 
                        / 2.f);

                    transformPtr->setPosition((transformPtr->getPosition()) * reflect(
                        transformPtr->getRotation(), 
                        collision.getNormal()
                    ) * (material.Bounciness + other.material.Bounciness) / 2.f);
                
                }

                return collision;
            }

            void update(const PhysicsEnviroment &env){
                if(abs(velocity.x) <= VELOCITY_TRESHOLD) velocity.x = 0;
				if(abs(velocity.z) <= VELOCITY_TRESHOLD) velocity.z = 0;

                transformPtr->getRotation() = norm(velocity);
                velocity /= vec3f(env.AirResistance, 1, env.AirResistance);
            
                velocity -= env.Gravity * mass;
				if(velocity.y < 0) velocity.y *= env.AirResistance;
            }

            RigidBody(
                PhysicsMaterial material,
                float mass,
                vec3f direction,
                vec3f velocity,
                Hitbox hitbox,

                bool isTransparent = false,
                bool isStatic = false
            ):  material(material),
                mass(mass),
                velocity(velocity),
                hitbox(hitbox),
                
                isTransparent(isTransparent),
                isStatic(isStatic) {transformPtr->getRotation() = direction;}

            RigidBody(){}
            ~RigidBody(){}
        };
    };
};