#pragma once
#include <Kinex/init.hpp>
#include <Kinex/internal.hpp>
#include "Object.hpp"

namespace knx{
    class DirectLightSource{
        irl::DirectionLight source;
        irl::Transform transform;
        
        void updateByTransform(){
            source.setDirection(transform.getRotation());
        }
        public:

        irl::Transform &getTransform(){return transform;}
        irl::DirectionLight &getSource(){return source;}

        void update(Object &obj){
            updateByTransform();
            source.update(*obj.getShaderPointer());
        }
        void update(irl::Shader &shd){
            updateByTransform();
            source.update(shd);
        }

        DirectLightSource(irl::DirectionLight source, irl::Transform transform): source(source), transform(transform) {}
        DirectLightSource(){}
        ~DirectLightSource(){}
    };
    class PointLightSource{
        irl::PointLight source;
        irl::Transform transform;
        
        void updateByTransform(){
            source.setPosition(transform.getPosition());
        }
        public:

        irl::Transform &getTransform(){return transform;}
        irl::PointLight &getSource(){return source;}

        void update(Object &obj){
            updateByTransform();
            source.update(*obj.getShaderPointer());
        }
        void update(irl::Shader &shd){
            updateByTransform();
            source.update(shd);
        }

        PointLightSource(irl::PointLight source, irl::Transform transform): source(source), transform(transform) {}
        PointLightSource(){}
        ~PointLightSource(){}
    };
    class SpotLightSource{
        irl::SpotLight source;
        irl::Transform transform;
        
        void updateByTransform(){
            source.setPosition(transform.getPosition());
            source.setDirection(transform.getRotation());
        }
        public:

        irl::Transform &getTransform(){return transform;}
        irl::SpotLight &getSource(){return source;}

        void update(Object &obj){
            updateByTransform();
            source.update(*obj.getShaderPointer());
        }
        void update(irl::Shader &shd){
            updateByTransform();
            source.update(shd);
        }

        SpotLightSource(irl::SpotLight source, irl::Transform transform): source(source), transform(transform) {}
        SpotLightSource(){}
        ~SpotLightSource(){}
    };
};