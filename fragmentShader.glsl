#version 330 core

#define MAX_POINT_LIGHTS 8

struct DirectionalLight
{
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
};

uniform sampler2D diffuse0;
uniform sampler2D specular0;
uniform sampler2D shadowMap;
uniform float shine;
uniform DirectionalLight directionalLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform int numberOfPointLights;
uniform vec3 camPos;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;
in vec4 fragPosLightSpace;

out vec4 FragColor;

vec3 calculateDirectionalLightAmbient()
{
    return directionalLight.ambient * vec3(texture(diffuse0, TexCoords));
}

vec3 calculatePointLightAmbient(PointLight pointLight)
{
    return pointLight.ambient * vec3(texture(diffuse0, TexCoords));
}

vec3 calculateDirectionalLightDiffuse(vec3 lightDirection, vec3 normalizedFragNormal)
{
    float diffuseOffset = max(dot(normalizedFragNormal, lightDirection), 0.0);
    return directionalLight.diffuse * diffuseOffset * vec3(texture(diffuse0, TexCoords));
}

vec3 calculatePointLightDiffuse(PointLight pointLight, vec3 lightDirection, vec3 normalizedFragNormal)
{
    float diffuseOffset = max(dot(normalizedFragNormal, lightDirection), 0.0);
    return pointLight.diffuse * diffuseOffset * vec3(texture(diffuse0, TexCoords));
}

vec3 calculateDirectionalLightSpecular(vec3 lightDirection, vec3 normalizedFragNormal)
{
    vec3 viewDirection = normalize(camPos - FragPos);
    vec3 reflectedLight = reflect(-lightDirection, normalizedFragNormal);
    float specularOffset = pow(max(dot(reflectedLight, viewDirection), 0.0), shine);
    return directionalLight.specular * specularOffset * vec3(texture(specular0, TexCoords));
}

vec3 calculatePointLightSpecular(PointLight pointLight, vec3 lightDirection, vec3 normalizedFragNormal)
{
    vec3 viewDirection = normalize(camPos - FragPos);
    vec3 reflectedLight = reflect(-lightDirection, normalizedFragNormal);
    float specularOffset = pow(max(dot(reflectedLight, viewDirection), 0.0), shine);
    return pointLight.specular * specularOffset * vec3(texture(specular0, TexCoords));
}

vec3 calculateDirectionalLightColor(float shadow)
{
    vec3 normalizedLightDirection = normalize(-directionalLight.direction);
    vec3 normalizedFragmentNormal = normalize(Normal);

    vec3 ambientLight  = calculateDirectionalLightAmbient();
    vec3 diffuseLight  = calculateDirectionalLightDiffuse(normalizedLightDirection, normalizedFragmentNormal);
    vec3 specularLight = calculateDirectionalLightSpecular(normalizedLightDirection, normalizedFragmentNormal);

    return ambientLight + (1.0 - shadow) * (diffuseLight + specularLight);
}

vec3 calculatePointLightColor(PointLight pointLight) 
{
    vec3 lightDirection = pointLight.position - FragPos;
    float distance = length(lightDirection);
    float attenuation = 1.0 / (pointLight.constant + pointLight.linear * distance + pointLight.quadratic * (distance * distance));

    vec3 normalizedLightDirection = normalize(lightDirection);
    vec3 normalizedFragmentNormal = normalize(Normal);

    vec3 ambientLight  = attenuation * calculatePointLightAmbient(pointLight);
    vec3 diffuseLight  = attenuation * calculatePointLightDiffuse(pointLight, normalizedLightDirection, normalizedFragmentNormal);
    vec3 specularLight = attenuation * calculatePointLightSpecular(pointLight, normalizedLightDirection, normalizedFragmentNormal);

    return ambientLight + diffuseLight + specularLight;
}

float calculateDirectionalShadow(vec4 fragPosLightSpace)
{
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    projCoords = projCoords * 0.5 + 0.5;

    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    float currentDepth = projCoords.z;

    vec3 normalizedLightDirection = normalize(-directionalLight.direction);
    vec3 normalizedFragmentNormal = normalize(Normal);

    float bias = max(0.05 * (1.0 - dot(normalizedFragmentNormal, normalizedLightDirection)), 0.005); 

    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    
    for(int x = -1; x <= 1; x++)
    {
        for(int y = -1; y <= 1; y++)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
            if (currentDepth - bias > pcfDepth) {
                shadow += 1.0;
            } 
        }    
    }
    shadow /= 9.0;
    
    return shadow;
}

void main()
{
    vec3 result = vec3(0.0);
    
    float shadow = calculateDirectionalShadow(fragPosLightSpace);
    result += calculateDirectionalLightColor(shadow); 

    for(int i = 0; i < numberOfPointLights; i++)
    {
        result += calculatePointLightColor(pointLights[i]);
    }
    
    FragColor = vec4(result, 1.0);
}
