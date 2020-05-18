#version 330 core
layout(location=0) in vec3 aPos;
layout(location=1) in vec3 aNormal;

out vec3 Normal;
out vec3 Position;

uniform mat4 mvp;
uniform mat4 u_model;

void main()
{
	Normal=mat3(transpose(inverse(u_model)))*aNormal;
	Position=vec3(u_model*vec4(aPos,1.0f));

	gl_Position=mvp*vec4(aPos,1.0f);
	gl_PointSize = gl_Position.z;   
}