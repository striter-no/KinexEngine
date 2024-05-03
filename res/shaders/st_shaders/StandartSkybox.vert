#version 460 core
in vec3 position;
out vec3 texCoord;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    texCoord = position;
    gl_Position = projection * view * vec4(position, 1.0);
}  