#pragma once
#include <Kinex/init.hpp>
#include "Lightning.hpp"


namespace knx{
    class LightningScene{
        
        map<string, DirectLightSource> dirLightSources;
        map<string, PointLightSource> pointLightSources;
        map<string, SpotLightSource> spotLightSources;

        void checkLightsEnable(irl::Shader &shader){
            if(dirLightSources.size() == 0){
                shader.use();
                    shader.setUniform("isDirectionLightEnabled", false);
                shader.de_use();
            }

            if(pointLightSources.size() == 0){
                shader.use();
                    shader.setUniform("isPointLightEnabled", false);
                shader.de_use();
            }

            if(spotLightSources.size() == 0){
                shader.use();
                    shader.setUniform("isSpotLightEnabled", false);
                shader.de_use();
            }
        }

        public:

        void addDirectionLightSource(string name, DirectLightSource source){dirLightSources[name] = source;}
        void addPointLightSource(string name, PointLightSource source){pointLightSources[name] = source;}
        void addSpotLightSource(string name, SpotLightSource source){spotLightSources[name] = source;}

        DirectLightSource &getDirectionLightSource(string name){ return dirLightSources[name]; }
        PointLightSource &getPointLightSource(string name){ return pointLightSources[name]; }
        SpotLightSource &getSpotLightSource(string name){ return spotLightSources[name]; }

        void deleteDirectionLightSource(string name){dirLightSources.erase(name);}
        void deletePointLightSource(string name){pointLightSources.erase(name);}
        void deleteSpotLightSource(string name){spotLightSources.erase(name);}

        void update(irl::Shader &shader){ checkLightsEnable(shader);
            for(auto &pr:dirLightSources) pr.second.update(shader);
            for(auto &pr:pointLightSources) pr.second.update(shader);
            for(auto &pr:spotLightSources) pr.second.update(shader);
        }

        void update(Object &object){ checkLightsEnable(*object.getShaderPointer());
            for(auto &pr:dirLightSources) pr.second.update(object);
            for(auto &pr:pointLightSources) pr.second.update(object);
            for(auto &pr:spotLightSources) pr.second.update(object);
        }

        LightningScene(){}
        ~LightningScene(){}
    };
}