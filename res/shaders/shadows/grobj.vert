#version 460 core
in vec3 position;
in vec3 normal;
in vec2 texCoord;

out VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} vs_out;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat3 normals_mat;

uniform mat4 lightSpaceMatrix;

void main()
{
    vs_out.FragPos = vec3(model * vec4(position, 1.0));
    vs_out.Normal = normals_mat * normal;
    vs_out.TexCoords = texCoord;
    vs_out.FragPosLightSpace = lightSpaceMatrix * vec4(vs_out.FragPos, 1.0);
    gl_Position = projection * view * model * vec4(position, 1.0);
}