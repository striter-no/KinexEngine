#pragma once
#include <Kinex/init.hpp>
#include "Texture.hpp"

namespace knx{
    namespace irl{
        class VBO{
            private:
            vector<float> vdata;
            int tsize = 0, num = 3;

            public:
            GLuint index;
            
            VBO(vector<float> data_, int num = 3, GLuint type = GL_STATIC_DRAW, bool bindAway = true){
                this->num = num;
                tsize = data_.size() / num;
                vdata = data_;

                glGenBuffers(1, &index);
                glBindBuffer(GL_ARRAY_BUFFER, index);
                    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vdata.size(), &vdata[0], type);
                if(bindAway) glBindBuffer(GL_ARRAY_BUFFER, 0);
            }

            void setup(){

                glGenBuffers(1, &index);
            }

            void buffer(vector<float> vdata, GLuint type = GL_STATIC_DRAW, bool binded = true){ this->vdata = vdata;
                if(!binded) use();
                glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vdata.size(), &vdata[0], type);
            }

            static VBO color_from_VBO(VBO vbo, vec3f color, int num = 3){
                vector<float> colors;
                for(int i = 0; i < vbo.get_vexsize()/num; i++){
                    colors.push_back(color.x);
                    colors.push_back(color.y);
                    colors.push_back(color.z);
                }
                return {colors};
            }

            vector<float> getRealData(){
                glBindBuffer(GL_ARRAY_BUFFER, index);
                GLint bufferSize = 0;
                glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &bufferSize);
                size_t numElements = bufferSize / sizeof(float);
                std::vector<float> bufferData(numElements);
                glGetBufferSubData(GL_ARRAY_BUFFER, 0, bufferSize, bufferData.data());
                glBindBuffer(GL_ARRAY_BUFFER, 0);

                return bufferData;
            }

            int get_vexsize(){return tsize;}
            int size(){return tsize * num;}
            void use(){glBindBuffer(GL_ARRAY_BUFFER, index);}
            void static de_use(){glBindBuffer(GL_ARRAY_BUFFER, 0);}
            void del_buf(){glDeleteBuffers(1, &index);}

            VBO(){;}
            ~VBO(){}
        };

        class VAO{
            public:
            GLuint index;

            static void de_use(){
                glBindVertexArray(0);
            }

            void use(){
                glBindVertexArray(index);
            }

            void setup(){
                glGenVertexArrays(1, &index);
            }

            void del_buf(){
                glDeleteVertexArrays(1, &index);
            }

            void printInfo(){
                glBindVertexArray(index); // Привязываем VAO

                GLint maxVertexAttribs;
                glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxVertexAttribs); // Получаем максимальное количество атрибутов

                std::cout << "VAO ID: " << index << std::endl;

                for (GLuint i = 0; i < maxVertexAttribs; ++i) {
                    GLint attributeEnabled;
                    glGetVertexAttribiv(i, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &attributeEnabled); // Проверяем, включен ли атрибут

                    if (attributeEnabled) {
                        GLint size, type, stride;
                        GLvoid* offset;
                        glGetVertexAttribiv(i, GL_VERTEX_ATTRIB_ARRAY_SIZE, &size); // Получаем размер атрибута
                        glGetVertexAttribiv(i, GL_VERTEX_ATTRIB_ARRAY_TYPE, &type); // Получаем тип данных атрибута
                        glGetVertexAttribiv(i, GL_VERTEX_ATTRIB_ARRAY_STRIDE, &stride); // Получаем шаг
                        glGetVertexAttribPointerv(i, GL_VERTEX_ATTRIB_ARRAY_POINTER, &offset); // Получаем смещение

                        std::cout << "Attribute " << i << ": enabled, Size: " << size << ", Type: " << type
                                << ", Stride: " << stride << ", Offset: " << reinterpret_cast<uintptr_t>(offset) << std::endl;
                    }
                }

                glBindVertexArray(0); // Отвязываем VAO
            }
        };

        class RBO{
            public:

            GLuint index;

            static void de_use(){
                glBindRenderbuffer(GL_RENDERBUFFER, 0);
            }

            void use(){
                glBindRenderbuffer(GL_RENDERBUFFER, index);
            }

            /*
            type:
            GL_DEPTH_ATTACHMENT
            GL_STENCIL_ATTACHMENT
            GL_DEPTH24_STENCIL8
            GL_COLOR_ATTACHMENT0
            */
            void buffer(vec2i res, GLuint type){
                glRenderbufferStorage(GL_RENDERBUFFER, type, res.x, res.y); 
            }

            void setup(){
                glGenRenderbuffers(1, &index);
            }

            void del_buf(){
                glDeleteFramebuffers(1, &index);
            }

            RBO(){}
        };

        class FBO{
            public:
            GLuint index;

            static void de_use(){
                glBindFramebuffer(GL_FRAMEBUFFER, 0);
            }

            void use(){
                glBindFramebuffer(GL_FRAMEBUFFER, index);
            }

            void setup(){
                glGenFramebuffers(1, &index);
            }

            void del_buf(){
                glDeleteFramebuffers(1, &index);
            }

            void attachTexture(Texture text){
                glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, text.index, 0);
            }

            void attachTexture(GLuint ind){
                glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ind, 0);
            }

            void attachRendBuff(RBO &rbo){
                glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo.index);
            }

            void finish(){
                if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
                    std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
            }

            FBO(){}
        };

    };
};