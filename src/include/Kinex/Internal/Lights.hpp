#pragma once
#include <Kinex/init.hpp>
#include "Shader.hpp"

namespace knx{
    namespace irl{

        // Light with direction
        class DirectionLight{
            vec3f direction;
            vec3f ambient;
            vec3f specular;
            vec3f diffuse;

            vec3f color;

            string name;
            LIGHT_TYPE type = DIRECTION_LIGHT;
            public:
            const LIGHT_TYPE &getType(){return type;}

            const string &getName(){return name;}

            const vec3f &getDirection(){return direction;}
            const vec3f &getAmbient(){return ambient;}
            const vec3f &getSpecular(){return specular;}

            void setDirection(vec3f direction){this->direction = direction;}
            void setAmbient(vec3f ambient){this->ambient = ambient;}
            void setSpecular(vec3f specular){this->specular = specular;}

            void update(Shader &shader){
                shader.use();
                    shader.setUniform("isDirectionLightEnabled", true);
                    shader.setUniform(name+".diffuse", diffuse);
                    shader.setUniform(name+".color", color);
                    shader.setUniform(name+".direction", direction);
                    shader.setUniform(name+".ambient", ambient);
                    shader.setUniform(name+".specular", specular);
                shader.de_use();
            }
            
            DirectionLight(vec3f direction, vec3f ambient, vec3f specular, vec3f diffuse, vec3f color, string name = "dirLight"): color(color), diffuse(diffuse), 
                name(name), 
                direction(direction), ambient(ambient), specular(specular) {}
            DirectionLight(vec3f ambient, vec3f specular, vec3f diffuse, vec3f color, string name = "dirLight"): color(color), diffuse(diffuse), 
                name(name), 
                direction(direction), ambient(ambient), specular(specular) {}

            DirectionLight(){}
            ~DirectionLight(){}
        };

        // Light with radius of illumination (without direction but with position)
        class PointLight{
            float constant = 1.0;
            float linear;
            float quadratic;
            
            vec3f position;
            vec3f ambient;
            vec3f diffuse;
            vec3f specular;

            vec3f color;

            string name;
            LIGHT_TYPE type = POINT_LIGHT;
            public:
            const LIGHT_TYPE &getType(){return type;}

            const string &getName(){return name;}

            const vec3f &getPosition(){return position;}
            void setPosition(const vec3f &val){position = val;}
            const float &getConstant(){return constant;}
            const float &getLinear(){return linear;}
            const float &getQuadratic(){return quadratic;}
            const vec3f &getAmbient(){return ambient;}
            const vec3f &getDiffuse(){return diffuse;}
            const vec3f &getSpecular(){return specular;}

            void setConstant(const float &constant){this->constant = constant;}
            void setLinear(const float &linear){this->linear = linear;}
            void setQuadratic(const float &quadratic){this->quadratic = quadratic;}
            void setAmbient(const vec3f &ambient){this->ambient = ambient;}
            void setDiffuse(const vec3f &diffuse){this->diffuse = diffuse;}
            void setSpecular(const vec3f &specular){this->specular = specular;}

            void update(Shader &shader){
                shader.use();
                    shader.setUniform("isPointLightEnabled", true);

                    shader.setUniform(name+".color", color);
                    shader.setUniform(name+".position", position);
                    shader.setUniform(name+".constant", constant);
                    shader.setUniform(name+".linear", linear);
                    shader.setUniform(name+".quadratic", quadratic);
                    shader.setUniform(name+".diffuse", diffuse);
                    shader.setUniform(name+".ambient", ambient);
                    shader.setUniform(name+".specular", specular);
                shader.de_use();
            }

            /*
            dist - distance to cover with illumination
            dist | linear | quadratic
            7       0.7	       1.8
            13      0.35	   0.44
            20      0.22	   0.20
            32      0.14	   0.07
            50      0.09	   0.032
            65      0.07	   0.017
            100     0.045      0.0075
            160     0.027	   0.0028
            200     0.022	   0.0019
            325     0.014	   0.0007
            600     0.007	   0.0002
            3250    0.0014     0.000007
            */
            PointLight(vec3f position, vec3f ambient, vec3f diffuse, vec3f specular, float linear, float quadratic, vec3f color, string name = "pointLight"): color(color), 
                name(name), position(position),
                ambient(ambient), diffuse(diffuse), specular(specular), 
                constant(constant), linear(linear), quadratic(quadratic) {}

            /*
            dist - distance to cover with illumination
            dist | linear | quadratic
            7       0.7	       1.8
            13      0.35	   0.44
            20      0.22	   0.20
            32      0.14	   0.07
            50      0.09	   0.032
            65      0.07	   0.017
            100     0.045      0.0075
            160     0.027	   0.0028
            200     0.022	   0.0019
            325     0.014	   0.0007
            600     0.007	   0.0002
            3250    0.0014     0.000007
            */
            PointLight(vec3f ambient, vec3f diffuse, vec3f specular, float linear, float quadratic, vec3f color, string name = "pointLight"): color(color), 
                name(name), 
                ambient(ambient), diffuse(diffuse), specular(specular), 
                constant(constant), linear(linear), quadratic(quadratic) {}
            PointLight(){}
            ~PointLight(){}
        };

        // Light with direction, radius of illumination and position
        class SpotLight{
            vec3f position;
            vec3f direction;
            float cutOff;
            float outerCutOff;
        
            float constant;
            float linear;
            float quadratic;
        
            vec3f ambient;
            vec3f diffuse;
            vec3f specular;

            vec3f color;

            string name;
            LIGHT_TYPE type = SPOT_LIGHT;
            public:
            const LIGHT_TYPE &getType(){return type;}

            const string &getName(){return name;}

            const vec3f &getPosition(){return position;}
            const vec3f &getDirection(){return direction;}
            const float &getCutOff(){return cutOff;}
            const float &getOuterCutOff(){return outerCutOff;}
            const float &getConstant(){return constant;}
            const float &getLinear(){return linear;}
            const float &getQuadratic(){return quadratic;}
            const vec3f &getAmbient(){return ambient;}
            const vec3f &getDiffuse(){return diffuse;}
            const vec3f &getSpecular(){return specular;}
            
            void setPosition(const vec3f &position){this->position = position;}
            void setDirection(const vec3f &direction){this->direction = direction;}
            void setCutOff(const float &cutOff){this->cutOff = cutOff;}
            void setOuterCutOff(const float &outerCutOff){this->outerCutOff = outerCutOff;}
            void setConstant(const float &constant){this->constant = constant;}
            void setLinear(const float &linear){this->linear = linear;}
            void setQuadratic(const float &quadratic){this->quadratic = quadratic;}
            void setAmbient(const vec3f &ambient){this->ambient = ambient;}
            void setDiffuse(const vec3f &diffuse){this->diffuse = diffuse;}
            void setSpecular(const vec3f &specular){this->specular = specular;}

            void update(Shader &shader){
                shader.use();
                    shader.setUniform("isSpotLightEnabled", true);

                    shader.setUniform(name+".color", color);
                    shader.setUniform(name+".direction", direction);
                    shader.setUniform(name+".position", position);
                    shader.setUniform(name+".cutOff", cutOff);
                    shader.setUniform(name+".outerCutOff", outerCutOff);
                    shader.setUniform(name+".constant", constant);
                    shader.setUniform(name+".linear", linear);
                    shader.setUniform(name+".quadratic", quadratic);
                    shader.setUniform(name+".diffuse", diffuse);
                    shader.setUniform(name+".ambient", ambient);
                    shader.setUniform(name+".specular", specular);
                shader.de_use();
            }

            /*
            dist - distance to cover with illumination
            dist | linear | quadratic
            7       0.7	       1.8
            13      0.35	   0.44
            20      0.22	   0.20
            32      0.14	   0.07
            50      0.09	   0.032
            65      0.07	   0.017
            100     0.045      0.0075
            160     0.027	   0.0028
            200     0.022	   0.0019
            325     0.014	   0.0007
            600     0.007	   0.0002
            3250    0.0014     0.000007
            */
            SpotLight(vec3f ambient, vec3f diffuse, vec3f specular, vec3f position, vec3f direction, float cutOff, float outerCutOff, float linear, float quadratic, vec3f color, string name = "spotLight"): color(color), 
                name(name), 
                ambient(ambient), diffuse(diffuse), specular(specular), 
                position(position), direction(direction), cutOff(cutOff), outerCutOff(outerCutOff), 
                constant(constant), linear(linear), quadratic(quadratic) {}
            
            /*
            dist - distance to cover with illumination
            dist | linear | quadratic
            7       0.7	       1.8
            13      0.35	   0.44
            20      0.22	   0.20
            32      0.14	   0.07
            50      0.09	   0.032
            65      0.07	   0.017
            100     0.045      0.0075
            160     0.027	   0.0028
            200     0.022	   0.0019
            325     0.014	   0.0007
            600     0.007	   0.0002
            3250    0.0014     0.000007
            */
            SpotLight(vec3f ambient, vec3f diffuse, vec3f specular, float cutOff, float outerCutOff, float linear, float quadratic, vec3f color, string name = "spotLight"): color(color), 
                name(name), 
                ambient(ambient), diffuse(diffuse), specular(specular), 
                cutOff(cutOff), outerCutOff(outerCutOff), 
                constant(constant), linear(linear), quadratic(quadratic) {}

            SpotLight(){}
            ~SpotLight(){}
        };
    };
};