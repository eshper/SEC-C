#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTex;

out vec4 Color;
out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;
out vec4 fragPosLightSpace;

uniform mat4 camMatrix;
uniform mat4 model;
uniform mat4 lightSpaceMatrix;

void main()
{
	FragPos = vec3(model * vec4(aPos, 1.0f));
	Color = vec4(aColor, 1.0f);
    Normal = transpose(inverse(mat3(model))) * aNormal;
	TexCoords = aTex;
    fragPosLightSpace = lightSpaceMatrix * vec4(FragPos,1.0);

	gl_Position = camMatrix * vec4(FragPos, 1.0);
}
