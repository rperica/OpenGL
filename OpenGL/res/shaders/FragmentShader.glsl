#version 330 core

layout(location=0) out vec4 color;
in vec2 TexCor;
uniform sampler2D u_Texture;

void main()
{
	vec4 texColor=texture(u_Texture,TexCor);
	color=texColor;
}

