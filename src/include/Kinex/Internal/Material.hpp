#pragma once
#include <Kinex/init.hpp>

namespace knx{
    namespace irl{
        class Material{
            float shininess;
            vec3f diffuse;
            vec3f specular;

            string name;
            public:

            const float &getShininess(){return shininess; }
            const vec3f &getDiffuse(){return diffuse; }
            const vec3f &getSpecular(){return specular; }

            void setShininess(const float &shininess){this->shininess = shininess; }
            void setDiffuse(const vec3f &diffuse){this->diffuse = diffuse; }
            void setSpecular(const vec3f &specular){this->specular = specular; }

            void update(Shader *shader){
                // shader->use();
                    shader->setUniform(name+".diffuse", diffuse);
                    shader->setUniform(name+".specular", specular);
                    shader->setUniform(name+".shininess", shininess);
                // shader->de_use();
            }

            Material(float shininess, vec3f diffuse, vec3f specular, string name = "material"): 
                name(name), shininess(shininess), diffuse(diffuse), specular(specular) {;}
            Material(string name): name(name){;}
            Material(){}
            ~Material(){}
        };
    }
}