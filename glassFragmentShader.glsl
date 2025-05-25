#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 FragColor;

uniform vec3 viewPos;
uniform vec3 lightPos;
uniform vec4 lightColor;
uniform float transparency;
uniform vec3 glassColor;

void main()
{
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 viewDir = normalize(viewPos - FragPos);

    // Diffuse lighting (optional for glass, but helps visibility)
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * vec3(lightColor);

    // Specular reflection (Blinn-Phong)
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(norm, halfwayDir), 0.0), 128.0); // Increase for sharper glass
    vec3 specular = spec * vec3(lightColor);

    // Final color: mostly specular with a hint of base color
    vec3 result = 0.1 * glassColor + 0.3 * diffuse + 0.6 * specular;

    FragColor = vec4(result, transparency);
}
