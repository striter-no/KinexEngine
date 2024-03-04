#pragma once

#include <re/init.hpp>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>
#include "Internal/enums.hpp"

void PrintOpenGLInfo(){
    std::string version = reinterpret_cast<const char *>(glGetString(GL_VERSION));
    std::string vendorInfo = reinterpret_cast<const char *>(glGetString(GL_VENDOR));
    std::string extensionsInfo = reinterpret_cast<const char *>(glGetString(GL_EXTENSIONS));
    std::cerr << "OpenGL version: " << version << std::endl;
    std::cerr << "OpenGL vendor: " << vendorInfo << std::endl;
    std::cerr << "Full OpenGL extensions list: " << extensionsInfo << std::endl;
}

vec3f from_g3(glm::vec3 v){ return {v.x, v.y, v.z}; }
glm::vec3 to_g3(vec3f v)  { return {v.x, v.y, v.z}; }


void printMat4(glm::mat4x4 matrix) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    cout<<endl;
}