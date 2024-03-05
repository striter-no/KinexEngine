#pragma once
#include <Kinex/init.hpp>
#include <Kinex/internal.hpp>
#include <Kinex/Internal/Transform.hpp>
#include "Camera.hpp"

namespace knx{
    // One texture MUST be the `currtexture`
    class Object{

        OBJECT_TYPE type;
        
        irl::VBO vbo; 
        irl::VBO *vbo_ptr = nullptr;
        irl::VAO vao;

        string name;
        irl::Transform transform;

        map<string, irl::Texture> textures;
        map<string, irl::Texture*> textures_ptr;
        irl::PhysicsMaterial *phyMaterial;
        irl::RigidBody rigidBody;
        irl::Material *material;
        irl::Shader *shader;
        irl::Mesh mesh;

        vec3f color;

        Camera *camera;
        GLuint drawMode;
        bool isPhyEnabled = false;
        public:
        irl::Mesh *meshPtr;

        irl::Material      *getMaterialPointer()   { return material; }
        irl::Shader        *getShaderPointer()     { return shader; }
        irl::RigidBody     *getRigidBodyPointer()  { return &rigidBody; }
        irl::VBO           *getVBOPointer()        { return vbo_ptr; }
        irl::RigidBody     &getRigidbody()         { return rigidBody; }
        irl::Transform     &getTransform()         { return transform; }
        const irl::Mesh    &getMesh()              { return mesh; }
        const irl::Texture &getTexture(string name){ return textures[name]; }
        
        const OBJECT_TYPE &getType(){ return type; }
        const map<string, irl::Texture> getTextures(){ return textures; }

        void setTexture(string name, const irl::Texture &val){ textures[name] = val;}
        void setMesh(const irl::Mesh &val){ mesh = val; }
        void setVBO(const irl::VBO &val){ vbo = val; }
        void setVBO(irl::VBO *val){ vbo_ptr = val; }

        void draw(){
            shader->use();

                auto view = camera->getTransform().getViewMatrix();
                auto model = transform.getModelMatrix();
                auto proj = camera->getProj();

                shader->setUniform("isTextureEnabled", textures.size()>0);

                // shader->setUniform("objColor", color);
                // shader->setUniform("viewPos", camera->getTransform().getPosition());
                shader->setUniform("view", view);
                shader->setUniform("model", model);
                shader->setUniform("projection", proj);
                if(mesh.getType() == VERTEX_NORMALS || mesh.getType() == VERTEX_NORMALS_TEXTURES){
                    shader->setUniform("normals_mat", glm::mat3(glm::transpose(glm::inverse(transform.getModelMatrix()))));
                }

                // material->update(shader);

                if(meshPtr->getType() == VERTEX_NORMALS_TEXTURES || meshPtr->getType() == VERTEX_TEXTURES){
                    int index = 0;
                    for(auto &pr: textures){
                        shader->setUniform(pr.first, pr.second, index);
                        index++;
                    }
                }

                meshPtr->draw();
            shader->de_use();
            // pause();
        }

        Object(string name, irl::Transform transform, Camera *camera, GLuint drawMode = GL_STATIC_DRAW):  drawMode(drawMode), 
               name(name), transform(transform), camera(camera) {
            type = RAW_OBJECT;
        }
        Object(string name, irl::Transform transform, Camera *camera, irl::Shader *shader, irl::Material *material, vec3f color = 1, GLuint drawMode = GL_STATIC_DRAW):  color(color), drawMode(drawMode), material(material), 
               name(name), transform(transform), camera(camera), shader(shader) {
            type = MESH_OBJECT;
        }
        Object(string name, irl::Transform transform, map<string, irl::Texture> textures, Camera *camera, irl::Shader *shader, irl::Material *material, vec3f color = 1, GLuint drawMode = GL_STATIC_DRAW): color(color), drawMode(drawMode), material(material), 
               name(name), transform(transform), textures(textures), camera(camera), shader(shader) {
            type = MESH_TEXTURES_OBJECT;
        }
        Object(string name, irl::Transform transform, irl::VBO *vbo, Camera *camera, irl::Shader *shader, irl::Material *material, vec3f color = 1, GLuint drawMode = GL_STATIC_DRAW): color(color), drawMode(drawMode), material(material), 
               name(name), transform(transform), vbo_ptr(vbo), camera(camera), shader(shader) {
            type = OPTIMIZED_OBJECT;
        }
        Object(string name, irl::Transform transform, irl::VBO *vbo, map<string, irl::Texture*> textures, Camera *camera, irl::Shader *shader, irl::Material *material, vec3f color = 1, GLuint drawMode = GL_STATIC_DRAW): color(color), drawMode(drawMode), material(material), 
               name(name), transform(transform), vbo_ptr(vbo), textures_ptr(textures), camera(camera), shader(shader) {
            type = OPTIMIZED_TEXTURED_OBJECT;
        }

        Object(){}
        ~Object(){
            cout<<"object destruct "<<to_stringb(glIsBuffer(mesh.getVBOPtr()->index)==GL_TRUE)<<endl;
        }
    };
};