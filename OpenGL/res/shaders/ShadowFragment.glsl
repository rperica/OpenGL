#version 330 core
out vec4 fragColor;

in VS_OUT
{
	vec2 texCor;
	vec3 normal;
	vec3 fragPos;
	vec4 fragPosLightSpace;
}fs_in;

uniform sampler2D diffuseMap;
uniform sampler2D specularMap;
uniform sampler2D shadowMap;

uniform vec3 lightPos;
uniform vec3 viewPos;

float ShadowCalculation(vec4 fragPosLightSpace)
{
	vec3 projCor=fragPosLightSpace.xyz/fragPosLightSpace.w;

	projCor=0.5*projCor+0.5;

	float closestDepth=texture(shadowMap,projCor.xy).r;
	float currentDepth=projCor.z;
	
	float bias=0.005;
	float shadow=currentDepth-bias>closestDepth ? 1.0 : 0.0;

	if(projCor.z>1.0)
	{
		shadow=0.0;
	}

	return shadow;
}

void main()
{
	vec3 diffColor=texture(diffuseMap,fs_in.texCor).rgb;
	vec3 specColor=texture(specularMap,fs_in.texCor).rgb;
	vec3 normal=normalize(fs_in.normal);

	vec3 lightColor=vec3(1.0);
	vec3 lightDir=normalize(lightPos-fs_in.fragPos);
	vec3 viewDir=normalize(viewPos-fs_in.fragPos);

	vec3 ambient=0.3*diffColor;

	float diffuse=max(dot(normal,lightDir),0.0);
	vec3  diffuseLight=lightColor*diffuse*diffColor;

	vec3 halfwayDir=normalize(viewDir+lightDir);
	float spec=pow(max(dot(halfwayDir,normal),0.0),64.0);
	vec3 specularLight=lightColor*spec*specColor;

	float shadow=ShadowCalculation(fs_in.fragPosLightSpace);
	vec3 lighting=(ambient+(1.0-shadow)*(diffuseLight+specularLight)); 

	fragColor=vec4(lighting,1.0);
}