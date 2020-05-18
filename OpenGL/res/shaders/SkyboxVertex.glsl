#version 330 core
layout(location=0) in vec3 aPos;

out vec3 texCor;
uniform mat4 mvp;

void main()
{
	texCor=aPos;
	vec4 pos=mvp*vec4(aPos,1.0f);
	gl_Position = pos.xyww;
}