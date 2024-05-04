#pragma once
#include <Kinex/init.hpp>
#include <Kinex/Internal/Shader.hpp>

namespace knx{
    class ScreenSurface{
        irl::Shader shader;

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
                glVertexAttribPointer(ipos, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);
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
                glVertexAttribPointer(ipos, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);
                vbo.de_use();
            vao.de_use();
        }

        void draw(){
            shader.use();
                vao.use(); vbo.use();
                    glDrawArrays(GL_TRIANGLES, 0, 6);
                vbo.de_use(); vao.de_use();
            shader.de_use();
        }

        ScreenSurface(){}
        ~ScreenSurface(){}
    };
};