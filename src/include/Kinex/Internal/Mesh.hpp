#pragma once
#include <Kinex/init.hpp>
#include "Buffers.hpp"
#include "Shader.hpp"

namespace knx{
    namespace irl{
        
        namespace meshes{

            vector<GLfloat> scaleCube(const vector<GLfloat>& cubeData, GLfloat scaleX, GLfloat scaleY, GLfloat scaleZ, bool scaleTexture = false, vec3f rescale = 1) {
                vector<GLfloat> result;
                result.reserve(cubeData.size());

                for (size_t i = 0; i < cubeData.size(); i += 8) {
                    result.push_back(cubeData[i] * scaleX);     // x position
                    result.push_back(cubeData[i + 1] * scaleY); // y position
                    result.push_back(cubeData[i + 2] * scaleZ); // z position
                    
                    for(int k = 0; k < 3; k++){
                        result.push_back(cubeData[i+3+k]); // нормали
                    }

                    if (scaleTexture) {
                        // Determine the face of the cube based on the normal vector
                        int face = -1;
                        if (cubeData[i+3] == 0.0f && cubeData[i+4] == 0.0f && cubeData[i+5] == -1.0f) {
                            face = 0; // back face
                        } else if (cubeData[i+3] == 0.0f && cubeData[i+4] == 0.0f && cubeData[i+5] == 1.0f) {
                            face = 1; // front face
                        } else if (cubeData[i+3] == 0.0f && cubeData[i+4] == -1.0f && cubeData[i+5] == 0.0f) {
                            face = 2; // bottom face
                        } else if (cubeData[i+3] == 0.0f && cubeData[i+4] == 1.0f && cubeData[i+5] == 0.0f) {
                            face = 3; // top face
                        } else if (cubeData[i+3] == -1.0f && cubeData[i+4] == 0.0f && cubeData[i+5] == 0.0f) {
                            face = 4; // left face
                        } else if (cubeData[i+3] == 1.0f && cubeData[i+4] == 0.0f && cubeData[i+5] == 0.0f) {
                            face = 5; // right face
                        }

                        // Scale the texture coordinates based on the face and the corresponding scaling factors
                        switch (face) {
                            case 0: // back face
                                result.push_back(cubeData[i+6] * (scaleX / rescale.x)); // текстурная координата X
                                result.push_back(cubeData[i+7] * (scaleZ / rescale.z)); // текстурная координата Y
                                break;
                            case 1: // front face
                                result.push_back(cubeData[i+6] * (scaleX / rescale.x)); // текстурная координата X
                                result.push_back(cubeData[i+7] * (scaleZ / rescale.z)); // текстурная координата Y
                                break;
                            case 2: // bottom face
                                result.push_back(cubeData[i+6] * (scaleX / rescale.x)); // текстурная координата X
                                result.push_back(cubeData[i+7] * (scaleY / rescale.y)); // текстурная координата Y
                                break;
                            case 3: // top face
                                result.push_back(cubeData[i+6] * (scaleX / rescale.x)); // текстурная координата X
                                result.push_back(cubeData[i+7] * (scaleY / rescale.y)); // текстурная координата Y
                                break;
                            case 4: // left face
                                result.push_back(cubeData[i+6] * (scaleZ / rescale.z)); // текстурная координата X
                                result.push_back(cubeData[i+7] * (scaleY / rescale.y)); // текстурная координата Y
                                break;
                            case 5: // right face
                                result.push_back(cubeData[i+6] * (scaleZ / rescale.z)); // текстурная координата X
                                result.push_back(cubeData[i+7] * (scaleY / rescale.y)); // текстурная координата Y
                                break;
                        }
                    } else {
                        // Keep the original texture coordinates
                        result.push_back(cubeData[i+6]); // текстурная координата X
                        result.push_back(cubeData[i+7]); // текстурная координата Y
                    }
                }

                return result;
            }

            vector<GLfloat> generatePlane(GLfloat width, GLfloat depth, bool scaleTexture = false, vec2f scalefac = 1) {
                vector<GLfloat> planeData;
                if(scaleTexture)
                    planeData = {
                        // positions          // normals           // texture coords
                        -width/2, 0.0f, -depth/2,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
                        width/2, 0.0f, -depth/2,  0.0f, 1.0f, 0.0f,  width/2 / scalefac.x, 0.0f,
                        width/2, 0.0f,  depth/2,  0.0f, 1.0f, 0.0f,  width/2 / scalefac.x, depth/2 / scalefac.y,

                        width/2, 0.0f,  depth/2,  0.0f, 1.0f, 0.0f,  width/2 / scalefac.x, depth/2 / scalefac.y,
                        -width/2, 0.0f,  depth/2,  0.0f, 1.0f, 0.0f,  0.0f, depth/2 / scalefac.y,
                        -width/2, 0.0f, -depth/2,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
                    };
                else
                    planeData = {
                        // positions          // normals           // texture coords
                        -width/2, 0.0f, -depth/2,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
                        width/2, 0.0f, -depth/2,  0.0f, 1.0f, 0.0f,  1, 0.0f,
                        width/2, 0.0f,  depth/2,  0.0f, 1.0f, 0.0f,  1, 1,

                        width/2, 0.0f,  depth/2,  0.0f, 1.0f, 0.0f,  1, 1,
                        -width/2, 0.0f,  depth/2,  0.0f, 1.0f, 0.0f,  0.0f, 1,
                        -width/2, 0.0f, -depth/2,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
                    };
                return planeData;
            }

            vector<GLfloat> generatePlaneWT(GLfloat width, GLfloat depth, bool scaleTexture = false, vec2f scalefac = 1) {
                vector<GLfloat> planeData = {
                        // positions          // normals           
                        -width/2, 0.0f, -depth/2,  0.0f, 1.0f, 0.0f,
                        width/2, 0.0f, -depth/2,  0.0f, 1.0f, 0.0f,
                        width/2, 0.0f,  depth/2,  0.0f, 1.0f, 0.0f,

                        width/2, 0.0f,  depth/2,  0.0f, 1.0f, 0.0f,
                        -width/2, 0.0f,  depth/2,  0.0f, 1.0f, 0.0f,
                        -width/2, 0.0f, -depth/2,  0.0f, 1.0f, 0.0f,
                    };
                return planeData;
            }

            vector<GLfloat> cubemesh = {
                -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
                0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
                0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
                0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
                -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

                -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

                0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
                0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

                -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
                0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
                -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
            };

            vector<GLfloat> cubemesh_clear = {
                -0.5f, -0.5f, -0.5f,
                0.5f, -0.5f, -0.5f,
                0.5f,  0.5f, -0.5f,
                0.5f,  0.5f, -0.5f,
                -0.5f,  0.5f, -0.5f,
                -0.5f, -0.5f, -0.5f,

                -0.5f, -0.5f,  0.5f,
                0.5f, -0.5f,  0.5f,
                0.5f,  0.5f,  0.5f,
                0.5f,  0.5f,  0.5f,
                -0.5f,  0.5f,  0.5f,
                -0.5f, -0.5f,  0.5f,

                -0.5f,  0.5f,  0.5f,
                -0.5f,  0.5f, -0.5f,
                -0.5f, -0.5f, -0.5f,
                -0.5f, -0.5f, -0.5f,
                -0.5f, -0.5f,  0.5f,
                -0.5f,  0.5f,  0.5f,

                0.5f,  0.5f,  0.5f,
                0.5f,  0.5f, -0.5f,
                0.5f, -0.5f, -0.5f,
                0.5f, -0.5f, -0.5f,
                0.5f, -0.5f,  0.5f,
                0.5f,  0.5f,  0.5f,

                -0.5f, -0.5f, -0.5f,
                0.5f, -0.5f, -0.5f,
                0.5f, -0.5f,  0.5f,
                0.5f, -0.5f,  0.5f,
                -0.5f, -0.5f,  0.5f,
                -0.5f, -0.5f, -0.5f,

                -0.5f,  0.5f, -0.5f,
                0.5f,  0.5f, -0.5f,
                0.5f,  0.5f,  0.5f,
                0.5f,  0.5f,  0.5f,
                -0.5f,  0.5f,  0.5f,
                -0.5f,  0.5f, -0.5f,
            };

            vector<GLfloat> cubemesh_nt_normals = {
                -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
                0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
                0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
                0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
                -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
                -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 

                -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
                0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
                0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
                0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
                -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
                -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

                -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
                -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
                -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
                -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
                -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
                -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

                0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
                0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
                0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
                0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
                0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
                0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

                -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
                0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
                0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
                0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

                -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
                0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
                0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
                0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
                -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
                -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
            };

            vector<GLfloat> cubemesh_txs_nrms = {
                // positions          // normals           // texture coords
                -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
                0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
                0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
                0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
                -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

                -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
                0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
                0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
                0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
                -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
                -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

                -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
                -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
                -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
                -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
                -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

                0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
                0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
                0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
                0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
                0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
                0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

                -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
                0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
                0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
                0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

                -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
                0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
                0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
                0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
                -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
                -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
            };

            vector<GLfloat> cubemesh_txsAllToOne_nrms = {
                // positions          // normals           // texture coords
                -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
                0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
                0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
                0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
                -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

                -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
                0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
                0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
                0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
                -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
                -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
                
                // Перевернутая грань 1
                -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
                -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
                -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
                -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
                -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

                // Перевернутая грань 2
                0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
                0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
                0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
                0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
                0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
                0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

                -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.f, 0.f,
                0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
                0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
                0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,

                -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.f, 0.f,
                0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
                0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
                0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
                -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
                -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f
            };
        }
        
        class Mesh{
            vector<float> data;
            MESH_TYPE type;
            int shift = 3;

            VBO vbo;
            VAO vao;

            public:
            const int &getShift(){ return shift; }
            const vector<float> &getData(){ return data; }
            const vec3f getPoint(int index){ return { data[index*shift], data[index*shift + 1], data[index*shift + 2] }; }
            const vec2f getTexturePoint(int index){ return { data[index*shift + 3], data[index*shift + 4] }; }
            const vec3f getNormalPoint(int index){ return { data[index*shift + 5], data[index*shift + 6], data[index*shift + 7] }; }
            const MESH_TYPE &getType(){return type;}

            unique_ptr<VBO> getVBOPtr(){return make_unique<VBO>(vbo);}
            unique_ptr<VAO> getVAOPtr(){return make_unique<VAO>(vao);}

            const VBO &getVBO(){return vbo;} VAO &getVAO(){return vao;}

            void setData(const vector<float> &data){ this->data = data; }
           
            void draw(function<void(void)> preDraw = [](){}){
                vao.use(); vbo.use();
                    preDraw();
                    glDrawArrays(GL_TRIANGLES, 0, size());
                vbo.de_use(); vao.de_use(); 
            }
            void setupBuffers(irl::Shader &shader){
                GLint ipos = shader.getAttribLoc("position"), itex = shader.getAttribLoc("texCoord"), inrms = shader.getAttribLoc("normal"); 
                
                switch(type){
                    case ONLY_VERTEXES: {
                        vao.setup();
                        vbo.setup();
                        vao.use();
                            
                            vbo.use(); vbo.buffer(data);
                            glEnableVertexAttribArray(ipos);
                            glVertexAttribPointer(ipos, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);
                            vbo.de_use();
                        vao.de_use();
                        break;
                    }
                    case VERTEX_NORMALS : {
                        vao.setup();
                        vbo.setup();
                        vao.use();
                            glEnableVertexAttribArray(ipos);
                            glEnableVertexAttribArray(inrms);
                        
                            vbo.use(); vbo.buffer(data);
                            glVertexAttribPointer(ipos, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), NULL);
                            glVertexAttribPointer(inrms, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
                            vbo.de_use();
                        vao.de_use();
                        break;
                    }
                    case VERTEX_NORMALS_TEXTURES : {

                        vao.setup();
                        vbo.setup();
                        vao.use();
                            glEnableVertexAttribArray(ipos);
                            glEnableVertexAttribArray(inrms);
                            glEnableVertexAttribArray(itex);

                            vbo.use(); vbo.buffer(data);
                            glVertexAttribPointer(ipos, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), NULL);
                            glVertexAttribPointer(inrms, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
                            glVertexAttribPointer(itex, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
                            vbo.de_use();
                        vao.de_use();
                        break;
                    }
                    case VERTEX_TEXTURES :         {
                        vao.setup();
                        vbo.setup();
                        vao.use();
                            glEnableVertexAttribArray(ipos);
                            glEnableVertexAttribArray(itex);
                            
                            vbo.use(); vbo.buffer(data);
                            glVertexAttribPointer(ipos, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), NULL);
                            glVertexAttribPointer(itex, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
                            vbo.de_use();
                        vao.de_use();

                        break;
                    }
                }
            }

            Mesh(string path, bool addNormals = false){ load(path, addNormals); }
            Mesh(vector<float> data, MESH_TYPE type, int shift = 3): data(data), type(type), shift(shift) {}
            ~Mesh(){}

            void load(string path, bool addNormals = false){

                vector<vec3f> vertexes, normals;
                vector<vec2f> uvertexes;

                for(string line : getFileLines(path)){
                    vector<string> splitted = split(line);
                    
                    if(splitted[0]=="v"){
                        float x = stof(splitted[1]), y = stof(splitted[2]), z = stof(splitted[3]);
                        vertexes.push_back({x, y, z});
                    } else if(splitted[0]=="vt"){
                        float x = stof(splitted[1]), y = stof(splitted[2]);
                        uvertexes.push_back({x, y});
                    } else if(splitted[0]=="vn"){
                        float x = stof(splitted[1]), y = stof(splitted[2]), z = stof(splitted[3]);
                        normals.push_back({x, y, z});
                    } else if(splitted[0]=="f"){
                        int a,b,c,na,nb,nc,ua,ub,uc;
                        a = stoi(split(splitted[1], '/')[0]);
                        b = stoi(split(splitted[2], '/')[0]);
                        c = stoi(split(splitted[3], '/')[0]);
                        if(uvertexes.size()>0){
                            ua = stoi(split(splitted[1], '/')[1]);
                            ub = stoi(split(splitted[2], '/')[1]);
                            uc = stoi(split(splitted[3], '/')[1]);}
                        
                        if(normals.size()>0){
                            na = stoi(split(splitted[1], '/')[2]);
                            nb = stoi(split(splitted[2], '/')[2]);
                            nc = stoi(split(splitted[3], '/')[2]);}
                        
                        vec3f enormal;
                        if(addNormals && !normals.size()>0){
                            enormal = normal(vertexes[a-1], vertexes[b-1], vertexes[c-1]);
                        }
                        

                        data.push_back(vertexes[a-1].x); data.push_back(vertexes[a-1].y); data.push_back(vertexes[a-1].z);
                        if(normals.size()>0) {data.push_back(normals[na-1].x); data.push_back(normals[na-1].y); data.push_back(normals[na-1].z);}
                        else if(addNormals){data.push_back(enormal.x); data.push_back(enormal.y); data.push_back(enormal.z);}
                        if(uvertexes.size()>0) {data.push_back(uvertexes[ua-1].x); data.push_back(uvertexes[ua-1].y);}

                        data.push_back(vertexes[b-1].x); data.push_back(vertexes[b-1].y); data.push_back(vertexes[b-1].z);
                        if(normals.size()>0) {data.push_back(normals[nb-1].x); data.push_back(normals[nb-1].y); data.push_back(normals[nb-1].z);}
                        else if(addNormals){data.push_back(enormal.x); data.push_back(enormal.y); data.push_back(enormal.z);}
                        if(uvertexes.size()>0) {data.push_back(uvertexes[ub-1].x); data.push_back(uvertexes[ub-1].y);}
                        
                        data.push_back(vertexes[c-1].x); data.push_back(vertexes[c-1].y); data.push_back(vertexes[c-1].z);
                        if(normals.size()>0) {data.push_back(normals[nc-1].x); data.push_back(normals[nc-1].y); data.push_back(normals[nc-1].z);}
                        else if(addNormals){data.push_back(enormal.x); data.push_back(enormal.y); data.push_back(enormal.z);}
                        if(uvertexes.size()>0) {data.push_back(uvertexes[uc-1].x); data.push_back(uvertexes[uc-1].y);}
                    }
                }
                bool isnormals = normals.size()>0;
                bool istexs = uvertexes.size()>0;
                
                if(isnormals){shift+=3;}
                if(istexs){shift+=2;}

                if(isnormals && !istexs)      type = VERTEX_NORMALS;
                else if(!isnormals && istexs) type = VERTEX_TEXTURES;
                else if(isnormals && istexs)  type = VERTEX_NORMALS_TEXTURES;
                else                          type = ONLY_VERTEXES;
            }

            Mesh(vector<float> data, bool normalsEn, bool textureEn): data(data) {
                bool isnormals = normalsEn;
                bool istexs = textureEn;
                
                if(isnormals){shift+=3;}
                if(istexs){shift+=2;}

                if(isnormals && !istexs)      type = VERTEX_NORMALS;
                else if(!isnormals && istexs) type = VERTEX_TEXTURES;
                else if(isnormals && istexs)  type = VERTEX_NORMALS_TEXTURES;
                else                          type = ONLY_VERTEXES;
            }

            Mesh(){}

            const vec3f operator[](int inx) {
                return getPoint(inx);
            }

            size_t size(){
                return data.size() / shift;
            }

            size_t dataSize(){
                return data.size();
            }
        };
    };
};