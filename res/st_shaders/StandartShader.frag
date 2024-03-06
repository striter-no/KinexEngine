#version 460 core

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

uniform bool isSpotLightEnabled;      uniform SpotLight spotLight;
uniform bool isPointLightEnabled;     uniform PointLight pointLight;
uniform bool isDirectionLightEnabled; uniform DirLight dirLight;
uniform bool isTextureEnabled;        uniform sampler2D currtexture;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
out vec4 FragColor;

uniform vec3 objColor;
uniform vec3 viewPos;
uniform Material material;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main(){
    
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 result = {0};
    // if(isPointLightEnabled) result += CalcPointLight(pointLight, norm, FragPos, viewDir);    
    // if(isDirectionLightEnabled) result += CalcDirLight(dirLight, norm, viewDir);
    if(isSpotLightEnabled)  result += CalcSpotLight(spotLight, norm, FragPos, viewDir);

    if(isTextureEnabled){ 
        vec2 txcd = vec2(TexCoord.x, 1.0f - TexCoord.y);
        result = mix(texture(currtexture, txcd).rgb, result, .8f);
    }

    FragColor = vec4(result * objColor, 1);
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
    return (ambient + diffuse + specular) * light.color;
}