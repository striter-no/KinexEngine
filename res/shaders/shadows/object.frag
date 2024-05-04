#version 460 core
out vec4 FragColor;

struct Material {
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 

struct DirLight {
    vec3 direction;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 color;
};

struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 color;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    float constant;
    float linear;
    float quadratic;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular; 
    vec3 color;      
};

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} fs_in;

uniform sampler2D shadowMap;

uniform bool isSpotLightEnabled;      uniform SpotLight spotLight;
uniform bool isPointLightEnabled;     uniform PointLight pointLight;
uniform bool isDirectionLightEnabled; uniform DirLight dirLight;
uniform bool isTextureEnabled;        uniform sampler2D currtexture;

uniform vec3 objColor;
uniform vec3 viewPos;
uniform Material material;

float ShadowCalculation(vec4 fragPosLightSpace);
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
    vec3 norm = normalize(fs_in.Normal);
    vec3 viewDir = normalize(viewPos - fs_in.FragPos);

    vec3 result = vec3(0);
    if(isPointLightEnabled) result += CalcPointLight(pointLight, norm, fs_in.FragPos, viewDir);    
    if(isDirectionLightEnabled) result += CalcDirLight(dirLight, norm, viewDir);
    if(isSpotLightEnabled)  result += CalcSpotLight(spotLight, norm, fs_in.FragPos, viewDir);

    if(isTextureEnabled){ 
        vec2 txcd = vec2(fs_in.TexCoords.x, 1.0f - fs_in.TexCoords.y);
        result = mix(texture(currtexture, txcd).rgb, result, .8f);
    }

    FragColor = vec4(vec3(1, 0, 1), 1.0); // result, 
}

float ShadowCalculation(vec4 fragPosLightSpace, vec3 normal, vec3 lightDir){
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;

    if(projCoords.z > 1.0)
        return 0.0;

    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // check whether current frag pos is in shadow
    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0;

    return shadow;
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir){
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading

    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance_ = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance_ + light.quadratic * (distance_ * distance_));    
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = light.ambient * vec3(material.diffuse);
    vec3 diffuse = light.diffuse * vec3(material.diffuse) * diff;
    
    vec3 a = light.specular;
    vec3 b = material.specular;
    vec3 c = vec3(spec);
    vec3 specular = a * b * c;
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular) * light.color;
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir){
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance_ = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance_ + light.quadratic * (distance_ * distance_));    
    // combine results
    vec3 ambient = light.ambient * vec3(material.diffuse);
    vec3 diffuse = light.diffuse * diff * vec3(material.diffuse);
    vec3 specular = light.specular * spec * vec3(material.specular);
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular) * light.color ;
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir){
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient = light.ambient * vec3(material.diffuse);
    vec3 diffuse = light.diffuse * diff * vec3(material.diffuse);
    vec3 specular = light.specular * spec * vec3(material.specular);
    return (ambient + (1.0 - ShadowCalculation(fs_in.FragPosLightSpace, normal, lightDir)) * (diffuse + specular)) * light.color;
}

