#version 330 core 
layout (location=0) in vec3 positions;
layout (location=1) in vec2 aTexCor;

out vec2 TexCor;
uniform mat4 u_MVP;

void main()
{
	gl_Position=u_MVP*vec4(positions,1.0f);
	TexCor=aTexCor;
}



