#version 330 core
layout(location=0) out vec4 color;

in vec2 textureCor;
uniform sampler2D tex;

const float offset=1.0/300.0;

void main()
{
	vec2 offsets[9]=vec2[](
		vec2(-offset,  offset),
		vec2(0.0f,     offset),
		vec2(offset,   offset),
		vec2(-offset,  0.0f),
		vec2(0.0f,     0.0f),
		vec2(offset,   0.0f),
		vec2(-offset, -offset),
		vec2(0.0f,    -offset),
		vec2(offset,  -offset)
	);

	float kernel[9]=float[]
	(
		-1.0, -1.0, -1.0,
		-1.0,  9,   -1.0,
		-1.0, -1.0, -1.0
	);

	vec3 col=vec3(0.0f);
	for(int i=0;i<9;i++)
	{
		col+=vec3(texture(tex,textureCor.st+offsets[i]))*kernel[i];
	}

	color=vec4(col,1.0);

	//color=texture(tex,textureCor);
}