#version 460 core
in vec3 ourColor;
in vec2 TexCoord;

out vec4 color;

uniform sampler2D ourTexture;
uniform sampler2D ourTexture2;

void main()
{
    vec2 txcd = vec2(TexCoord.x, 1.0f - TexCoord.y);

    // color = texture(ourTexture, TexCoord);
    // color = texture(ourTexture, TexCoord);// * vec4(ourColor, 1.0f);
    color = mix(texture(ourTexture, txcd), texture(ourTexture2, txcd), 0.2);
}
