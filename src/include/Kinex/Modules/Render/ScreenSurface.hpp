#pragma once
#include <Kinex/init.hpp>
#include <Kinex/Internal/Shader.hpp>

namespace knx{
    class ScreenSurface{
        irl::Shader shader;
        GLuint textureId;
        bool textureEnabled = false;

        irl::VAO vao;
        irl::VBO vbo;

        public:

        ScreenSurface(
            irl::Shader shader
        ): shader(shader) {
            
            vector<GLfloat> vertices = {
                // Позиции        // Текстурные координаты
                -1.0f, 1.0f,
                -1.0f, -1.0f,
                1.0f, -1.0f,

                -1.0f, 1.0f,
                1.0f, -1.0f,
                1.0f, 1.0f
            };

            GLint ipos = shader.getAttribLoc("position");

            vao.setup();
            vbo.setup();
            vao.use();
                glEnableVertexAttribArray(ipos);

                vbo.use(); vbo.buffer(vertices);
                glVertexAttribPointer(ipos, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);
                vbo.de_use();
            vao.de_use();
        }

        ScreenSurface(
            string path
        ): shader(path) {
            
            vector<GLfloat> vertices = {
                // Позиции        // Текстурные координаты
                -1.0f, 1.0f,
                -1.0f, -1.0f,
                1.0f, -1.0f,

                -1.0f, 1.0f,
                1.0f, -1.0f,
                1.0f, 1.0f
            };

            GLint ipos = shader.getAttribLoc("position");

            vao.setup();
            vbo.setup();
            vao.use();
                glEnableVertexAttribArray(ipos);

                vbo.use(); vbo.buffer(vertices);
                glVertexAttribPointer(ipos, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);
                vbo.de_use();
            vao.de_use();
        }

        void setupShader(string path){ shader = irl::Shader(path); }
        void setupShader(irl::Shader shader){ this->shader = shader; }

        void setTexture(GLuint id){
            textureId = id;
            textureEnabled = true;

            vector<GLfloat> vertices = {
                // Позиции        // Текстурные координаты
                -1.0f, 1.0f,      -1.0f, 1.0f,
                -1.0f, -1.0f,      -1.0f, -1.0f,
                1.0f, -1.0f,      1.0f, -1.0f,

                -1.0f, 1.0f,      -1.0f, 1.0f,
                1.0f, -1.0f,      1.0f, -1.0f,
                1.0f, 1.0f,      1.0f, 1.0f
            };

            GLint ipos = shader.getAttribLoc("position"), itex = shader.getAttribLoc("texCoords");

            vao.setup();
            vbo.setup();
            vao.use();
                glEnableVertexAttribArray(ipos);
                glEnableVertexAttribArray(itex);

                vbo.use(); vbo.buffer(vertices);
                glVertexAttribPointer(ipos, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), NULL);
                glVertexAttribPointer(itex, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
                vbo.de_use();
            vao.de_use();
        }

        void draw(){
            shader.use();
                vao.use(); vbo.use();
                if(textureEnabled) glBindTexture(GL_TEXTURE_2D, textureId);
                    glDrawArrays(GL_TRIANGLES, 0, 6);
                if(textureEnabled) glBindTexture(GL_TEXTURE_2D, 0);
                vbo.de_use(); vao.de_use();
            shader.de_use();
        }

        ScreenSurface(){}
        ~ScreenSurface(){}
    };
};