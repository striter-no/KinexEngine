#pragma once
#include <Kinex/init.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <Kinex/Exta/stb_image.h>

namespace knx{
    namespace irl{
        class Texture{
            int width, height, cnt;
            u_char *img = nullptr;
            
            TEXTURE_TYPE type;
            public:
            GLuint index;

            Texture(string path, bool repeated = false, bool freeThis = false){
                if(!is_fileexists(path)){
                    throw invalid_argument("texture: cannot open image: "+path);
                }
                img = stbi_load(path.c_str(), &width, &height, &cnt, 0);
                type = DATA_TEXTURE;

                glGenTextures(1, &index);
                glBindTexture(GL_TEXTURE_2D, index);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

                    if(repeated) {
                        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
                        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                    }
                    
                    glTexImage2D(GL_TEXTURE_2D, 0, cnt == 4 ? GL_RGBA : GL_RGB, width, height, 0, cnt == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, img);
                glGenerateMipmap(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, 0);
                if(freeThis) {
                    stbi_image_free(img);
                    type = STANDART_GL_TEXTURE;
                }
            }

            Texture(vec2i size, bool repeated = false){
                type = EMPTY_GL_TEXTURE;

                glGenTextures(1, &index);
                glBindTexture(GL_TEXTURE_2D, index);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

                    if(repeated) {
                        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
                        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                    }
                    
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.x, size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
                glGenerateMipmap(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, 0);
            }

            Texture(GLuint index){
                this->index = index;
                type = STANDART_GL_TEXTURE;
            }

            void loadFromFile(string path, bool freeThis = false){
                type = DATA_TEXTURE;
                img = stbi_load(path.c_str(), &width, &height, &cnt, 0);

                glGenTextures(1, &index);
                glBindTexture(GL_TEXTURE_2D, index);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                    glTexImage2D(GL_TEXTURE_2D, 0, cnt == 4 ? GL_RGBA : GL_RGB, width, height,
                                                0, cnt == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, img);
                glGenerateMipmap(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, 0);
                // if(freeThis) {
                //     stbi_image_free(img);
                //     type = STANDART_GL_TEXTURE;
                // }
            }

            void loadFromData(u_char *data, int w, int h, int cnt_ = 3, bool freeThis = false){
                img = data;
                type = PTR_DATA_TEXTURE;

                width = w;
                height = h;
                cnt = cnt_;
                glGenTextures(1, &index);
                glBindTexture(GL_TEXTURE_2D, index);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                    glTexImage2D(GL_TEXTURE_2D, 0, cnt == 4 ? GL_RGBA : GL_RGB, width, height,
                                                0, cnt == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, 0);
                // if(freeThis) {
                //     stbi_image_free(img);
                //     type = STANDART_GL_TEXTURE;
                // }
            }

            void use(){
                glBindTexture(GL_TEXTURE_2D, index);
            }

            void de_use(){
                glBindTexture(GL_TEXTURE_2D, 0);
            }

            Texture(){}
            ~Texture(){
                // if(type!=PTR_DATA_TEXTURE && (type == DATA_TEXTURE || type == GL_DATA_TEXTURE)){
                //     stbi_image_free(img);
                // }
            }
        };
    };
};