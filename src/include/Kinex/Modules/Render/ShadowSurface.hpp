#pragma once
#include <Kinex/init.hpp>
#include <Kinex/Internal/Shader.hpp>

namespace knx{
    class ShadowSurface{
        vec2i resolution;
        GLuint depthMapFBO;

        glm::mat4 lightProjection;
        glm::mat4 lightView;
        glm::mat4 lightSpaceMatrix;

        irl::Shader selfShader;
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
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

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

        void drawScene(
            vec3f lightPosition,
            vec3f lightLookPosition,
            vec2i frameResolution,
            function<void(irl::Shader*)> preRenderFunc,
            function<void(int)> renderFunc,
            float near_plane = 1.f, 
            float far_plane = 7.5f
        ){
            lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
            lightView = glm::lookAt(to_g3(lightPosition), to_g3(lightLookPosition), glm::vec3( 0.0f, 1.0f,  0.0f));
            lightSpaceMatrix = lightProjection * lightView;

            glViewport(0, 0, resolution.x, resolution.y);
                glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
                    glClear(GL_DEPTH_BUFFER_BIT);
                    selfShader.use();
                    
                        selfShader.setUniform("lightSpaceMatrix", lightSpaceMatrix);
                        preRenderFunc(&selfShader);
                    
                    selfShader.de_use();
                glBindFramebuffer(GL_FRAMEBUFFER, 0);
            
            glViewport(0, 0, frameResolution.x, frameResolution.y);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                renderFunc(id);
        }

        ShadowSurface(){}
        ~ShadowSurface(){}
    };
};