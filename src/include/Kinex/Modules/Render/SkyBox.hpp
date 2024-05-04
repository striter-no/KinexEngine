#pragma once
#include <Kinex/init.hpp>
#include <Kinex/Internal/Shader.hpp>
#include <Kinex/Internal/Mesh.hpp>
#include <Kinex/Modules/Render/CubeMap.hpp>
#include <Kinex/Modules/Camera.hpp>

namespace knx{
    class SkyBox{
        irl::Shader mainShader;
        irl::Mesh mainMesh;

        CubeMap cubeMap;
        public:
        bool isInited = false;

        SkyBox(
            string pathToDir,
            string shaderPath,
            string fileFormat = "jpg"
        ): isInited(true) {
            cubeMap = CubeMap({
                pathToDir + "/right."+fileFormat,
                pathToDir + "/left."+fileFormat,
                pathToDir + "/top."+fileFormat,
                pathToDir + "/bottom."+fileFormat,
                pathToDir + "/front."+fileFormat,
                pathToDir + "/back."+fileFormat
            });

            mainShader = irl::Shader(shaderPath);

            mainMesh = irl::Mesh(knx::irl::meshes::cubemesh_clear, ONLY_VERTEXES);
            mainMesh.setupBuffers(mainShader);
        }

        void draw(Camera &camera){
            glDepthMask(GL_FALSE);
                mainShader.use();
                    mainShader.setUniform("view", glm::mat4x4(glm::mat3x3(camera.getTransform().getViewMatrix())));
                    mainShader.setUniform("projection", camera.getProj());

                    mainMesh.draw([&](){cubeMap.use();});
                    cubeMap.de_use();
                mainShader.de_use();
            glDepthMask(GL_TRUE);
        }

        SkyBox(){}
        ~SkyBox(){}
    };
};