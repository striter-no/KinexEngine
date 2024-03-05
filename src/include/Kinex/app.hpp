#pragma once
#include "internal.hpp"
#include "modules.hpp"

namespace knx{
    class Core{

        vec2i res;
        vec4f background;
        string title;

        irl::Window *window;
        Input inputSystem;
        Time time;
        PhysicsScene physicsScene;
        LightningScene lightScene;
        
        Camera camera;
        FPController fpc; bool isFPCSetted = false;
        CameraController camcont; bool isCACSetted = false;

        map<string, Object*> gameObjects;
        map<string, irl::Shader*> shaders;
        map<string, irl::Texture> textures;
        map<string, irl::Material> materials;

        public:

        void addMaterial(string name, irl::Material material){materials[name] = material;}
        void addObject(string name, Object *object){gameObjects[name] = object;}
        void addShader(string name, irl::Shader *shader){shaders[name] = shader;}
        void addTexture(string name, irl::Texture texture){textures[name] = texture;}

        void setFPController(FPController cont){ fpc = cont; isFPCSetted = true;}
        void setCAController(CameraController cont){ camcont = cont; isCACSetted = true;}

        bool isFPControllerSetted(){return isFPCSetted;}
        bool isCAControllerSetted(){return isCACSetted;}

        FPController &getFPController(){return fpc;}
        FPController *getFPControllerPointer(){return &fpc;}

        CameraController &getCAController(){return camcont;}
        CameraController *getCAControllerPointer(){return &camcont;}

        Time &getTime(){return time;}
        Time *getTimePointer(){return &time;}

        Camera &getCamera(){return camera;}
        Camera *getCameraPointer(){return &camera;}

        LightningScene &getLightScene(){return lightScene;}
        irl::Window &getWindow(){return *window;}
        Input &getInputSystem(){return inputSystem;}
        PhysicsScene &getPhysicsScene(){return physicsScene;}

        LightningScene *getLightScenePointer(){return &lightScene;}
        irl::Window *getWindowPointer(){return window;}
        Input *getInputSystemPointer(){return &inputSystem;}
        PhysicsScene *getPhysicsScenePointer(){return &physicsScene;}

        Object &getObject(string name){return *gameObjects[name];}
        irl::Material getMaterial(string name){return materials[name];}
        irl::Shader &getShader(string name){return *shaders[name];}
        irl::Texture &getTexture(string name){return textures[name];}

        Object *getObjectPointer(string name){return gameObjects[name];}
        irl::Material *getMaterialPointer(string name){return &materials[name];}
        irl::Shader *getShaderPointer(string name){return shaders[name];}
        irl::Texture *getTexturePointer(string name){return &textures[name];}

        map<string, Object*> &getObjects(){return gameObjects;}

        bool isRunning(){
            return window->isOpen();
        }

        void update(
            function<void()> drawFunc,
            function<void()> updateFunc,
            function<void()> preDrawFunc,
            function<void()> postDrawFunc){
            window->pollEvents();
            window->update(
                [&](){
                    for(auto &pr: gameObjects){
                        // pr.second->getShaderPointer()->printInfo();
                        // lightScene.update(*pr.second);
                        pr.second->draw();
                    }
                    drawFunc();
                }, 
                [&](){
                    if(isFPCSetted) fpc.update(inputSystem, physicsScene);
                    if(isCACSetted) camcont.update();

                    inputSystem.update();
                    physicsScene.update();
                    
                    updateFunc();
                }, 
                preDrawFunc, 
                postDrawFunc
            );
            window->swap();
            
        }

        void setupCamera(irl::Transform transform, float speed, float sens, float near_, float far_){
            camera = Camera(transform, speed, sens);
            camera.setProjection(res, near_, far_);
        }

        Core(
            vec2i res,
            vec4f background,
            string title,
            irl::PhysicsEnviroment env,
            bool isPhysicsEnabled = true
        ):  res(res),
            background(background),
            title(title) {
            
            window = new irl::Window(title, res, background);
            inputSystem = Input(window);
            physicsScene = PhysicsScene(env, isPhysicsEnabled);
            time = Time(window);
        }

        Core(){}
        ~Core(){
            window->terminate();
        }
    };
};