#version 460 core
in vec2 position;
in vec2 texCoord;

out vec2 TexCoords;

void main()
{
    TexCoords = texCoord;
    gl_Position = vec4(position.x, position.y, 0, 1.0);
}