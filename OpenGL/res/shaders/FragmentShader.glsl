#version 330 core

layout(location=0) out vec4 color;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCor;

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light 
{
	vec3 position;
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

};

uniform vec3 view;
uniform vec3 lightPos;

uniform Material material;
uniform Light light;

void main()
{
	
	vec3 ambient=light.ambient*texture(material.diffuse,TexCor).rgb;

	vec3 norm=normalize(Normal);
	vec3 lightDir=normalize(light.position-FragPos);
	float diff=max(dot(norm,lightDir),0.0f);
	vec3 diffuse=light.diffuse*diff*texture(material.diffuse,TexCor).rgb;

	float specularStrength=0.5f;
	vec3 viewDir=normalize(view-FragPos);
	vec3 reflectDir=reflect(-lightDir,norm);
	float spec=pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
	vec3 specular=light.specular*spec*texture(material.specular,TexCor).rgb;

	vec3 result=ambient+diffuse+specular;
	color=vec4(result,1.0f);
}

