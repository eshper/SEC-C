#version 330 core

in vec4 Color;
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 FragColor;

// Material textures
uniform sampler2D diffuse0;
uniform sampler2D specular0;

// Light
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
    // Material properties from textures
    vec3 diffuseColor = texture(diffuse0, TexCoords).rgb;
    vec3 specularColor = texture(specular0, TexCoords).rgb;

    // Lighting
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);

    // View direction and reflection
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0); // Shininess is hardcoded here

    vec3 ambient = 0.1 * diffuseColor;
    vec3 diffuse = diff * diffuseColor;
    vec3 specular = spec * specularColor;

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}