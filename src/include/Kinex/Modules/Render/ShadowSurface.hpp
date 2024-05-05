#pragma once
#include <Kinex/init.hpp>
#include <Kinex/Internal/Shader.hpp>
#include "ScreenSurface.hpp"

namespace knx{
    class ShadowSurface{
        vec2i resolution;
        GLuint depthMapFBO;

        glm::mat4 lightProjection;
        glm::mat4 lightView;
        glm::mat4 lightSpaceMatrix;

        irl::Shader selfShader;
        
        irl::Shader depthQuadShader;
        ScreenSurface depthQuad;

        public:
        GLuint id;

        ShadowSurface(vec2i mapResolution): resolution(mapResolution) {
            glGenFramebuffers(1, &depthMapFBO);
            
            glGenTextures(1, &id);
            glBindTexture(GL_TEXTURE_2D, id);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
                        resolution.x, resolution.y, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

            glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, id, 0);
            glDrawBuffer(GL_NONE);
            glReadBuffer(GL_NONE);
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            GLenum fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
            if (fboStatus != GL_FRAMEBUFFER_COMPLETE) {
                std::cout << "Framebuffer not complete: " << fboStatus << std::endl;
            }
        }

        void setupShader(irl::Shader shader){ selfShader = shader; }
        void setupShader(string path){ selfShader = irl::Shader(path); }
        void setupDepthQuadShader(string path){ depthQuadShader = irl::Shader(path); depthQuad.setupShader(path); depthQuad.setTexture(id);}
        void setupDepthQuadShader(irl::Shader shader){ depthQuadShader = shader; depthQuad.setupShader(shader); depthQuad.setTexture(id);}

        void drawScene(
            vec3f lightPos,
            vec3f lightLookAt,
            vec2i frameResolution,
            function<void(irl::Shader*)> preRenderFunc,
            function<void(int)> renderFunc,
            bool renderQuad = false,
            float near_plane = 1.f, 
            float far_plane = 7.5f
        ){
            // Настройка
            lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
            lightView = glm::lookAt(to_g3(lightPos), to_g3(lightLookAt), {0, 1, 0});
            lightSpaceMatrix = lightProjection * lightView;

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            
            selfShader.use();
            selfShader.setUniform("lightSpaceMatrix", lightSpaceMatrix);

            glViewport(0, 0, resolution.x, resolution.y);
            glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
                glClear(GL_DEPTH_BUFFER_BIT);
                preRenderFunc(&selfShader);
            glBindFramebuffer(GL_FRAMEBUFFER, 0);

            selfShader.de_use();
            glViewport(0, 0, frameResolution.x, frameResolution.y);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            if(renderQuad) depthQuad.draw();
            else renderFunc(id);
        }

        ShadowSurface(){}
        ~ShadowSurface(){}
    };
};

