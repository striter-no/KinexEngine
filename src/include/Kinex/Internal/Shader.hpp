#pragma once
#include <Kinex/init.hpp>
#include "Texture.hpp"

namespace knx{
    namespace irl{
        class Shader{
        
            GLuint LoadShader(string fileName, GLuint type){
                string file = join(getFileLines(fileName), '\n');

                const char *cfile = file.c_str();
                GLuint shader = glCreateShader(type);
                
                glShaderSource(shader, 1, &cfile, NULL);
                glCompileShader(shader);
                GLint ok;
                GLchar log[2000];
                glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);
                if(!ok){

                    glGetShaderInfoLog(shader, 2000, NULL, log);
                    cout<<fileName<<" error:\n";
                    printf("%s", log);

                    printv(processVector<string, string>(getFileLines(fileName), [&](int inx, string el) -> string{
                        return to_string(inx) + " | " + el;
                    }), false, '\n');
                }

                return shader;
            }

            GLuint getProgram(vector<GLuint> shaders){
                GLint ok;
                GLchar log[2000];

                GLuint program = glCreateProgram();
                for(GLuint shader : shaders) glAttachShader(program, shader);
                glLinkProgram(program);

                glGetProgramiv(program, GL_LINK_STATUS, &ok);
                if(!ok){
                    glGetProgramInfoLog(program, 2000, NULL, log);
                    printf("%s", log);
                    return 0;
                }

                return {program};
            }
            
            public:
            GLuint prog;
            vector<GLuint> ids;
            bool status = false;

            // Type - GL_..._SHADER
            void reload(string path, GLuint type){ids.clear();ids.push_back(LoadShader(path, type));}
            void newShader(string path, GLuint type){ids.push_back(LoadShader(path, type));}
            GLint getAttribLoc(string name){return glGetAttribLocation(prog, name.c_str());}
            GLint getUniformLoc(string name){return glGetUniformLocation(prog, name.c_str());}
            void setUniform(string name, bool val){setUniform(name, val ? 1 : 0);}
            void setUniform(string name, float val){glUniform1f(getUniformLoc(name), val);}
            void setUniform(string name, int val){glUniform1i(getUniformLoc(name), val);}
            void setUniform(string name, vec2f val){glUniform2f(getUniformLoc(name), val.x, val.y);}
            void setUniform(string name, vec3f val){glUniform3f(getUniformLoc(name), val.x, val.y, val.z);}
            void setUniform(string name, vec4f val){glUniform4f(getUniformLoc(name), val.x, val.y, val.z, val.w);}
            void setUniform(string name, glm::mat4x4 val){glUniformMatrix4fv(getUniformLoc(name), 1, GL_FALSE, glm::value_ptr(val));}
            void setUniform(string name, glm::mat3x3 val){glUniformMatrix3fv(getUniformLoc(name), 1, GL_FALSE, glm::value_ptr(val));}
            void setUniform(string name, Texture val, int indx){setUniformTextureIndex(name, val.index, indx);}
            void use(){glUseProgram(prog); status = true;}
            void de_use(){glUseProgram(0); status = false;}

            void printInfo(){
                GLint numAttributes;
                glGetProgramiv(prog, GL_ACTIVE_ATTRIBUTES, &numAttributes);

                if(numAttributes > 0) {
                    std::cout << "Number of active attributes: " << numAttributes << std::endl;
                    for(GLint i = 0; i < numAttributes; ++i) {
                        char attributeName[256];
                        GLsizei attributeNameLength;
                        GLint attributeSize;
                        GLenum attributeType;
                        glGetActiveAttrib(prog, i, sizeof(attributeName), &attributeNameLength, &attributeSize, &attributeType, attributeName);
                        std::cout << "Attribute #" << i << ": " << attributeName << std::endl;
                    }
                } else {
                    std::cout << "No active attributes found." << std::endl;
                }
                cout<<endl;

                GLint numUniforms;
                glGetProgramiv(prog, GL_ACTIVE_UNIFORMS, &numUniforms);

                if(numUniforms > 0) {
                    std::cout << "Number of active uniforms: " << numUniforms << std::endl;
                    for(GLint i = 0; i < numUniforms; ++i) {
                        char uniformName[256];
                        GLsizei uniformNameLength;
                        GLint uniformSize;
                        GLenum uniformType;
                        glGetActiveUniform(prog, i, sizeof(uniformName), &uniformNameLength, &uniformSize, &uniformType, uniformName);
                        std::cout << "Uniform #" << i << ": " << uniformName << std::endl;
                    }
                } else {
                    std::cout << "No active uniforms found." << std::endl;
                }
            }

            void setUniformTextureIndex(string name, GLuint tex, int indx){
                glActiveTexture(GL_TEXTURE0 + indx);
                glBindTexture(GL_TEXTURE_2D, tex);
                glUniform1i(getUniformLoc(name), indx);
            }

            void finish(){
                prog = getProgram(ids);
                for(GLuint id:ids){
                    glDeleteShader(id);
                }
                ids.clear();
            }

            // Type - GL_..._SHADER
            Shader(string path){
                newShader(path+".frag", GL_FRAGMENT_SHADER);
                newShader(path+".vert", GL_VERTEX_SHADER);
                finish();
            }

            Shader(){}
        };
    };
};