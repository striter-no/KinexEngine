#pragma once
#include <Kinex/init.hpp>
#include <Kinex/Internal/Shader.hpp>

namespace knx{
    class RenderSurface{
        vec2f size;
        vec2f pos;
        irl::Shader shader;

        GLuint textId;
        GLuint fbo;
        GLuint rbo;
        GLuint quadVBO;
        GLuint quadVAO;

        public:
        bool isEnabled = false;

        void link(){glBindFramebuffer(GL_FRAMEBUFFER, fbo);}
        void finish(){glBindFramebuffer(GL_FRAMEBUFFER, 0);}
        void draw(){
            glTranslatef(pos.x, pos.y, 0);
            shader.use();
            glBindVertexArray(quadVAO);
            glBindTexture(GL_TEXTURE_2D, textId);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glBindVertexArray(0);
            shader.de_use();
        }

        const GLuint &getTexture(){
            return textId;
        }

        RenderSurface(vec2f pos, vec2f size, irl::Shader shader, string posAttr = "position", string textureAttr = "texCoord"):
                    pos(pos), size(size), shader(shader), isEnabled(true) {
            GLfloat vertices[] = {
                // Позиции        // Текстурные координаты
                -1.0f, 1.0f,      -1.0f, 1.0f,
                -1.0f, -1.0f,      -1.0f, -1.0f,
                1.0f, -1.0f,      1.0f, -1.0f,

                -1.0f, 1.0f,      -1.0f, 1.0f,
                1.0f, -1.0f,      1.0f, -1.0f,
                1.0f, 1.0f,      1.0f, 1.0f
            };

            // Создание и настройка VAO и VBO для прямоугольника
            glGenVertexArrays(1, &quadVAO);
            glGenBuffers(1, &quadVBO);
            glBindVertexArray(quadVAO);
            glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
            glEnableVertexAttribArray(shader.getAttribLoc(posAttr));
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);
            glEnableVertexAttribArray(shader.getAttribLoc(textureAttr));
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);

            // Создание буфера кадра (FBO)
            glGenFramebuffers(1, &fbo);
            glBindFramebuffer(GL_FRAMEBUFFER, fbo);

            // Создание текстуры для рендеринга
            glGenTextures(1, &textId);
            glBindTexture(GL_TEXTURE_2D, textId);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textId, 0);

            glGenRenderbuffers(1, &rbo);
            glBindRenderbuffer(GL_RENDERBUFFER, rbo); 
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, size.x, size.y);  
            glBindRenderbuffer(GL_RENDERBUFFER, 0);

            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

            // Проверка статуса FBO
            if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
                std::cout << "Error: Framebuffer is not complete!" << std::endl;

            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        RenderSurface(vec2f pos, vec2f size, string shaderPath, string posAttr = "position", string textureAttr = "texCoord"):
                    pos(pos), size(size), shader(shaderPath), isEnabled(true) {
            GLfloat vertices[] = {
                // Позиции        // Текстурные координаты
                -1.0f, 1.0f,      -1.0f, 1.0f,
                -1.0f, -1.0f,      -1.0f, -1.0f,
                1.0f, -1.0f,      1.0f, -1.0f,

                -1.0f, 1.0f,      -1.0f, 1.0f,
                1.0f, -1.0f,      1.0f, -1.0f,
                1.0f, 1.0f,      1.0f, 1.0f
            };

            // Создание и настройка VAO и VBO для прямоугольника
            glGenVertexArrays(1, &quadVAO);
            glGenBuffers(1, &quadVBO);
            glBindVertexArray(quadVAO);
            glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
            glEnableVertexAttribArray(shader.getAttribLoc(posAttr));
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);
            glEnableVertexAttribArray(shader.getAttribLoc(textureAttr));
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);

            // Создание буфера кадра (FBO)
            glGenFramebuffers(1, &fbo);
            glBindFramebuffer(GL_FRAMEBUFFER, fbo);

            // Создание текстуры для рендеринга
            glGenTextures(1, &textId);
            glBindTexture(GL_TEXTURE_2D, textId);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textId, 0);

            glGenRenderbuffers(1, &rbo);
            glBindRenderbuffer(GL_RENDERBUFFER, rbo); 
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, size.x, size.y);  
            glBindRenderbuffer(GL_RENDERBUFFER, 0);

            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

            // Проверка статуса FBO
            if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
                std::cout << "Error: Framebuffer is not complete!" << std::endl;

            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        void deleteBuffers(){
            glDeleteFramebuffers(1, &fbo);
            glDeleteTextures(1, &textId);
            glDeleteVertexArrays(1, &quadVAO);
            glDeleteBuffers(1, &quadVBO);
            glDeleteRenderbuffers(1, &rbo);
        }

        RenderSurface(){}
        ~RenderSurface(){}
    };

    class CubeMap{
        int width, height, nrChannels;
        public:
        GLuint id;

        const int &getWidth(){return width;}
        const int &getHeight(){return height;}
        const int &getChanels(){return nrChannels;}

        CubeMap(vector<string> paths){
            glGenTextures(1, &id);
            glBindTexture(GL_TEXTURE_CUBE_MAP, id);

            int width, height, nrChannels;
            for (unsigned int i = 0; i < paths.size(); i++)
            {
                unsigned char *data = stbi_load(paths[i].c_str(), &width, &height, &nrChannels, 0);
                if (data)
                {
                    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
                                0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
                    );
                    stbi_image_free(data);
                }
                else
                {
                    std::cout << "Cubemap texture failed to load at path: " << paths[i] << std::endl;
                    stbi_image_free(data);
                }
            }
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        }

        void use(){
            glBindTexture(GL_TEXTURE_CUBE_MAP, id);
        }
        void deuse(){
            glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
        }

        CubeMap(){}
        ~CubeMap(){}
    };

    class ShadowSurface{
        vec2i resolution;
        GLuint depthMapFBO;

        glm::mat4 lightProjection;
        glm::mat4 lightView;
        glm::mat4 lightSpaceMatrix;

        irl::Shader selfShader;
        public:
        GLuint id;

        /*
        How to use:
        surf.use();
        surf.lookFrom(...);
            renderScene();
        surf.finish();
            updateScene();
            renderScene();
        surf.deuse();
        */
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
        }

        void setupShader(irl::Shader shader){
            selfShader = shader;
        }

        void setupShader(string path){
            selfShader = irl::Shader(path);
        }

        void lookFrom(
            vec3f position, 
            vec3f lookPosition, 
            float near_plane = 1.f, 
            float far_plane = 7.5f
        ){
            lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
            lightView = glm::lookAt(to_g3(position), to_g3(lookPosition), glm::vec3( 0.0f, 1.0f,  0.0f));
            lightSpaceMatrix = lightProjection * lightView;

            selfShader.use();
            selfShader.setUniform("lightSpaceMatrix", lightSpaceMatrix);
        }

        void use(){
            glViewport(0, 0, resolution.x, resolution.y);
            glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
            glClear(GL_DEPTH_BUFFER_BIT);
        }

        void finish(vec2i frameResolution){
            selfShader.de_use();

            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            glViewport(0, 0, frameResolution.x, frameResolution.y);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glBindTexture(GL_TEXTURE_2D, id);
        }

        void deuse(){
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        ShadowSurface(){}
        ~ShadowSurface(){}
    };
};