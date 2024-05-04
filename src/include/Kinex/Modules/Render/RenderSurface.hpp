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
};