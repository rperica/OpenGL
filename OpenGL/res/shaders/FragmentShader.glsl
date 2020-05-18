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

	float constant;
	float linear;
	float quadratic;

	float cutOff;
	float outOff;
};

struct DirectionLight 
{
	vec3 direction;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight
{
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

struct SpotLight
{
	vec3 direction;
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;

	float cutOff;
	float outOff;
};

vec3 CalcDirLight(DirectionLight light,vec3 normal,vec3 viewDir);
vec3 CalcPointLight(PointLight light,vec3 normal,vec3 viewDir,vec3 fragPos);
vec3 CalcSpotLight(SpotLight light,vec3 normal,vec3 viewDir,vec3 fragPos);

uniform vec3 view;
uniform vec3 lightPos;

uniform Material material;
uniform Light light;

uniform DirectionLight dirLight;
uniform PointLight pointLights[4];
uniform SpotLight spotLight;

void main()
{
	vec3 norm=normalize(Normal);
	
	vec3 viewDir=normalize(view-FragPos);

	vec3 result=CalcDirLight(dirLight,norm,viewDir);

	for(int i=0;i<4;i++)
	{
		result+=CalcPointLight(pointLights[i],norm,viewDir,FragPos);
	}
	
	result+=CalcSpotLight(spotLight,norm,viewDir,FragPos);

	color=vec4(result,1.0f);
}

vec3 CalcDirLight(DirectionLight light,vec3 normal,vec3 viewDir)
{
	vec3 lightDir=normalize(-light.direction);
	
	vec3 ambient=light.ambient*texture(material.diffuse,TexCor).rgb;

	float diff=max(dot(lightDir,normal),0.0f);
	vec3 diffuse=light.diffuse*diff*texture(material.diffuse,TexCor).rgb;
	
	vec3 reflectDir=reflect(-lightDir,normal);
	float spec=pow(max(dot(viewDir,reflectDir),0.0f),material.shininess);
	vec3 specular=light.specular*spec*texture(material.specular,TexCor).rgb;

	return (ambient+diffuse+specular);
}

vec3 CalcPointLight(PointLight light,vec3 normal,vec3 viewDir,vec3 fragPos)
{
	vec3 lightDir=normalize(light.position-fragPos);

	vec3 ambient=light.ambient*texture(material.diffuse,TexCor).rgb;

	float diff=max(dot(lightDir,normal),0.0f);
	vec3 diffuse=light.diffuse*diff*texture(material.diffuse,TexCor).rgb;
	
	vec3 reflectDir=reflect(-lightDir,normal);
	float spec=pow(max(dot(viewDir,reflectDir),0.0f),material.shininess);
	vec3 specular=light.specular*spec*texture(material.specular,TexCor).rgb;

	float dist=distance(light.position,fragPos);
	float atten=1.0f/(light.constant+light.linear*dist+light.quadratic*dist*dist);
	
	diffuse*=atten;
	specular*=atten;
	
	return (ambient+diffuse+specular);
}

vec3 CalcSpotLight(SpotLight light,vec3 normal,vec3 viewDir,vec3 fragPos)
{
	vec3 lightDir=normalize(light.position-fragPos);

	vec3 ambient=light.ambient*texture(material.diffuse,TexCor).rgb;

	float diff=max(dot(lightDir,normal),0.0f);
	vec3 diffuse=light.diffuse*diff*texture(material.diffuse,TexCor).rgb;
	
	vec3 reflectDir=reflect(-lightDir,normal);
	float spec=pow(max(dot(viewDir,reflectDir),0.0f),material.shininess);
	vec3 specular=light.specular*spec*texture(material.specular,TexCor).rgb;

	float dist=distance(light.position,fragPos);
	float atten=1.0f/(light.constant+light.linear*dist+light.quadratic*dist*dist);
	
	diffuse*=atten;
	specular*=atten;

	float theta=dot(lightDir,normalize(-light.direction));
	float epsilon=light.cutOff-light.outOff;
	float intensity=clamp((theta-light.outOff)/epsilon,0,1);

	diffuse*=intensity;
	specular*=intensity;

	return (ambient+diffuse+specular);
}