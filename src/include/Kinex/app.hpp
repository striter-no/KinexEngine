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
        SkyBox skybox;
        FPController fpc; bool isFPCSetted = false;
        CameraController camcont; bool isCACSetted = false;

        vec3f fogColor = {0.8f, 0.8f, 0.8f};
        float fogDensity = 0.02f;
        bool fogEnabled = false;

        map<string, Object*> gameObjects;
        map<string, irl::Shader*> shaders;
        map<string, irl::Texture> textures;
        map<string, irl::Material> materials;

        RenderSurface postProcSurf;
        ScreenSurface preProcSurf;
        ShadowSurface planeShadows;

        irl::Material defaultMaterial = {1, {1.f}, 1.f};
        irl::Mesh defaultCubeMesh = irl::Mesh(knx::irl::meshes::cubemesh_txs_nrms, true, true);
        irl::Mesh defaultCubeMeshWithoutNormals = irl::Mesh(knx::irl::meshes::cubemesh, false, true);
        irl::Mesh defaultCubeOnlyMesh = irl::Mesh(knx::irl::meshes::cubemesh_clear, false, false);

        public:

        void addMaterial(string name, irl::Material material){materials[name] = material;}
        void addObject(string name, Object *object, bool addRB = true, bool isTransperent = false, bool isStatic = false){
            gameObjects[name] = object; 
            if(addRB){
                object->initRigidBody({0, 0, 0}, 1, {0}, {0}, isTransperent, isStatic);
                physicsScene.addRigidBody(name, object->getRigidBodyPointer());
                physicsScene.getRigidBody(name)->linkTransform(object->getTransformPointer());
            }
        }
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
        irl::Material &getDefaultMaterial(){return defaultMaterial; }

        Object *getObjectPointer(string name){return gameObjects[name];}
        irl::Material *getMaterialPointer(string name){return &materials[name];}
        irl::Shader *getShaderPointer(string name){return shaders[name];}
        irl::Texture *getTexturePointer(string name){return &textures[name];}
        irl::Material *getDefaultMaterialPointer(){return &defaultMaterial; }

        map<string, Object*> &getObjects(){return gameObjects;}

        void setupPostprocessingFromFile(string shaderPath, std::string posAttr = "position", std::string textureAttr = "texCoord"){
            postProcSurf = RenderSurface({0}, window->getResolution(), shaderPath, posAttr, textureAttr);
        }

        void setupPostprocessingFromName(string shaderName, std::string posAttr = "position", std::string textureAttr = "texCoord"){
            postProcSurf = RenderSurface({0}, window->getResolution(), getShader(shaderName), posAttr, textureAttr);
        }

        void setupPostprocessingFromMemoty(irl::Shader &shader, std::string posAttr = "position", std::string textureAttr = "texCoord"){
            postProcSurf = RenderSurface({0}, window->getResolution(), shader, posAttr, textureAttr);
        }

        void setupSkyBox(string pathToImages, string fileFormat = "jpg", string pathToSkyBoxShader = "res/shaders/st_shaders/StandartSkyBox"){
            skybox = SkyBox(pathToImages, pathToSkyBoxShader, fileFormat);
        }

        void setupFog(vec3f color, float density, bool setBackgoundColor = true){
            fogColor = color;
            fogDensity = density;
            fogEnabled = true;

            if(setBackgoundColor){
                window->setClearColor(color);
            }
        }

        bool isRunning(){
            return window->isOpen();
        }

        void update(
            function<void()> drawFunc,
            function<void()> updateFunc,
            function<void()> preDrawFunc,
            function<void()> postDrawFunc){
            
            auto render = [&](int){
                for(auto &pr: gameObjects){
                    // lightScene.update(*pr.second->getShaderPointer());
                    pr.second->getShaderPointer()->use();
                        pr.second->getShaderPointer()->setUniformTextureIndex("shadowMap", planeShadows.id, pr.second->getTextures().size());
                        pr.second->getShaderPointer()->setUniform("lightPos", vec3f{0, 37, -7});
                        pr.second->getShaderPointer()->setUniform("fogColor", fogColor);
                        pr.second->getShaderPointer()->setUniform("fogDensity", fogDensity);
                        pr.second->getShaderPointer()->setUniform("fogEnabled", fogEnabled);
                    pr.second->getShaderPointer()->de_use();
                    pr.second->draw();
                }
                drawFunc();
            };

            auto preRender = [&](irl::Shader *shader){
                for(auto &pr: gameObjects){
                    pr.second->draw(false, shader, {{"model", true}});
                }
                drawFunc();
            };
            
            window->pollEvents();
            window->update(
                [&](){
                    if(skybox.isInited){
                        skybox.draw(camera);
                    }

                    planeShadows.drawScene(
                        irl::Transform{
                            {0, 37, -7},
                            {0.f, -0.5f, 0.0}
                        },
                        vec2f_ti(window->getResolution()), 
                        preRender, 
                        render
                    );
                }, 
                [&](){
                    if(isFPCSetted) fpc.update(inputSystem, physicsScene);
                    if(isCACSetted) camcont.update();

                    inputSystem.update();
                    physicsScene.update();
                    
                    updateFunc();
                }, 
                [&](){
                    if(postProcSurf.isEnabled){
                        postProcSurf.link();
                    }

                    preDrawFunc();
                },
                [&](){
                    if(postProcSurf.isEnabled){
                        postProcSurf.finish();
                        glClearColor(1, 1, 1, 1);
                        glClear(GL_COLOR_BUFFER_BIT);
                        postProcSurf.draw();
                    }
                    postDrawFunc();
                }
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

            planeShadows = ShadowSurface(res); // {3000, 3000}
            planeShadows.setupShader("res/shaders/shadows/shadow");
            planeShadows.setupDepthQuadShader("res/shaders/shadows/showdepth");
        }

        Core(){}
        ~Core(){
            window->terminate();
        }
    };
};