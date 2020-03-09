#version 330 core 
layout (location=0) in vec3 positions;
layout (location=1) in vec3 aNormal;
layout (location=2) in vec2 aTextureCordinates;

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCor;

uniform mat4 u_MVP;
uniform mat4 u_model;

void main()
{
	FragPos=vec3(u_model*vec4(positions,1.0f));

	Normal=mat3(transpose(inverse(u_model)))*aNormal;

	TexCor=aTextureCordinates;

	gl_Position=u_MVP*vec4(positions,1.0f);
}



