#version 330 core 
layout (location=0) in vec3 positions;
layout (location=1) in vec2 aTexCor;

out vec2 TexCor;

void main()
{
	gl_Position=vec4(positions,1.0f);
	TexCor=aTexCor;
}



