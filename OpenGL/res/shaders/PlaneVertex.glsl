#version 330 core
layout(location=0) in vec3 aPos;
layout(location=2) in vec2 aTexCor;

out vec2 TexCor;

uniform mat4 mvp;

void main()
{
	TexCor=aTexCor;
	gl_Position=mvp*vec4(aPos,1.0f);
}