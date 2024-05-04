#pragma once
#include <Kinex/init.hpp>
#include <Kinex/Internal/Shader.hpp>

namespace knx{
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

            // int width, height, nrChannels;
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
        void de_use(){
            glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
        }

        CubeMap(){}
        ~CubeMap(){}
    };
};