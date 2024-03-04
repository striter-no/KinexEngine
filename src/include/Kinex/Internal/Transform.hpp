#pragma once
#include <Kinex/init.hpp>

namespace knx{
    namespace irl{
        class Transform{
            
            vec3f v_position;
            vec3f v_rotation;
            vec3f v_scale;
            vec3f v_size;

            vec3f v_front;
            vec3f v_up;
            vec3f v_right;

            glm::mat4x4 ident = glm::identity<glm::mat4x4>();

            public:

            vec3f &getPosition(){return v_position;}
            vec3f &getRotation(){return v_rotation;}
            vec3f &getScale(){return v_scale;}
            vec3f &getOriginalSize(){return v_size;}
            const vec3f getLookPosition(){return v_position + getFront();}
            const vec3f getSize(){return v_scale * v_size; }
            const vec3f &getLookDirection(){return getFront();}

            const vec3f &getFront(){
                v_front = norm(vec3f{
                    cos(rad(v_rotation.x)) * cos(rad(v_rotation.y)), 
                    sin(rad(v_rotation.y)), 
                    sin(rad(v_rotation.x)) * cos(rad(v_rotation.y))
                });
                return v_front;
            }
            const vec3f &getUp(){
                v_up = norm(cross(getRight(), getFront()));
                return v_up;
            }
            const vec3f &getRight(){
                v_right = norm(cross(getFront(), {0, 1, 0}));
                return v_right;
            }

            glm::mat4x4 getPositionMatrix(vec3f position = -1){ 
                // if(position != -1.f) 
                //     this->v_position = position; 
                return glm::translate(ident, to_g3(v_position)); 
            }

            glm::mat4x4 getViewMatrix(vec3f position = -1, vec3f rotation = -1){
                // if(rotation != -1.f) 
                //     this->v_rotation = rotation; 
                // if(position != -1.f) 
                //     this->v_position = position;
                return glm::lookAt(
                    to_g3(v_position), 
                    to_g3(v_position + getFront()), 
                    to_g3(getUp())
                ); 
            }

            glm::mat4x4 getRotationMatrix(vec3f rotation = -1){ 
                // if(rotation != -1.f) 
                //     this->v_rotation = rotation; 
                return  glm::rotate(
                            glm::rotate(
                                glm::rotate( ident, 
                                v_rotation.x, {1, 0, 0}), 
                            v_rotation.y, {0,  1, 0}), 
                        v_rotation.z, {0, 0,   1}); 
            }

            glm::mat4x4 getScaleMatrix(vec3f scale = -1){ 
                if(scale != -1.f) 
                    this->v_scale = scale; 
                return glm::scale(ident, to_g3(v_scale)); 
            }

            glm::mat4x4 getModelMatrix(vec3f position = -1, vec3f rotation = -1, vec3f scale = -1){ 
                return getPositionMatrix(position) * 
                       getRotationMatrix(rotation) * 
                       getScaleMatrix(scale); 
            }

            void setPosition(const vec3f &position){this->v_position = position;}
            void setRotation(const vec3f &rotation){this->v_rotation = rotation;}
            void setScale(const vec3f &scale){this->v_scale = scale;}
            void setSize(const vec3f &size){this->v_size = size;}

            Transform &rotate(const Transform &other){ v_rotation += other.v_rotation; return *this;}
            Transform &scale(const Transform &other){ v_scale += other.v_scale; return *this;}
            Transform &translate(const Transform &other){ v_position += other.v_position; return *this;}

            Transform &rotate(const vec3f &val){ v_rotation += val; return *this;}
            Transform &scale(const vec3f &val){ v_scale += val; return *this;}
            Transform &translate(const vec3f &val){ v_position += val; return *this;}

            Transform(vec3f v_position, vec3f v_rotation = 0.f, vec3f v_scale = 1.f, vec3f v_size = 0.f):
                    v_position(v_position), v_rotation(v_rotation), v_scale(v_scale), v_size(v_size) {}

            Transform(){}
            ~Transform(){}
        };
    }
};