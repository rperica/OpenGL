#version 330 core
out vec4 color;

in vec3 Normal;
in vec3 Position;

uniform vec3 camPos;
uniform samplerCube skybox;

void main()
{
	vec3 I=normalize(Position-camPos);
	vec3 R=reflect(I,normalize(Normal));
	color=vec4(texture(skybox,R).rgb,1.0f);
}