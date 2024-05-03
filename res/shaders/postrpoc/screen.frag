#version 460 core

out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D screenTexture;

void main()
{
    vec3 col = texture(screenTexture, (TexCoords+1)/2).rgb;
    // Примените здесь эффекты постобработки к col
    
    // col = mix(vec3((TexCoords+1)/2, 0), col, 0.5f);

    // col = 1 - col;

    FragColor = vec4(col, 1.0); //col, 
}