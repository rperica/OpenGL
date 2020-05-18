#version 330 core
layout(location=0) out vec4 color;

in vec2 TexCor;

//uniform vec3 colores;
uniform sampler2D tex;
void main()
{
	//color=vec4(vec3(1.0f),1.0f);
	color=vec4(texture(tex,TexCor).rgb,1.0f);
}