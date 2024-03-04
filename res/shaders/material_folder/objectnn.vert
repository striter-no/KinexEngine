#version 460 core
in vec3 position;
in vec2 texCoord;

out vec3 FragPos;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
    gl_Position = projection * view * model * vec4(position, 1.0f);
    FragPos = vec3(model * vec4(position, 1.f));
    TexCoord = texCoord;
}

// object to light