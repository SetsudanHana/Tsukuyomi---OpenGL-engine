#version 400
layout(location = 20) in vec4 worldVertex;
layout(location = 30) in vec2 texture_coords;
layout(location = 40) in vec4 Normal;
in float layer;

uniform sampler2D grass;
uniform sampler2D ground;
uniform sampler2D snow;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 lightAmbient;
uniform vec3 viewPos;
uniform float lightRadius;
uniform float specularShiness;
uniform float specularPower;

out vec4 frag_colour;

vec4 calculatePointLight(vec4 WorldVertex, vec4 WorldNormal, vec4 Texel, vec3 ViewPos, vec3 LightPos, vec3 LightColor, vec3 LightAmbient, float LightRadius, float SpecularShiness, float SpecularPower)
{
  vec4 FragColour;
  vec3 NormNormal = normalize(WorldNormal.xyz);
  vec3 lightVec = normalize(LightPos - WorldVertex.xyz);
  vec3 view = normalize(ViewPos - WorldVertex.xyz);

  vec3 LightDiffuse = dot(NormNormal, lightVec) * LightColor;

  vec3 H = normalize( lightVec + view );
  float Is = clamp(dot(NormNormal, H), 0.0f, 1.0f);
  vec3 Specular = pow( Is, SpecularShiness ) * ((SpecularShiness + 8.0f) / (8.0f * 3.14159265f)) * LightDiffuse;

  //Fresnel
  //vec3 SpecularAlbedo = vec3(0.971519f, 0.959915f, 0.915324f); //Z mesha
  vec3 SpecularAlbedo = Texel.rgb; //Duzo uproszczenie Kolor DiffuseMesha = Kolor Specular
  vec3 Fresnel = SpecularAlbedo;
  Fresnel += (1.0f - SpecularAlbedo) * pow((1.0f - clamp(dot(H, lightVec), 0.0f, 1.0f)), 5.0f);

  float lightDist = length(LightPos - WorldVertex.xyz);
  lightDist /= LightRadius;
  float atten = 1.0f/((lightDist * lightDist) + 1);

  FragColour.rgb = LightAmbient * Texel.rgb + atten * LightDiffuse * Texel.rgb + atten * Specular * Fresnel * SpecularPower, 1.0f;
  FragColour.a = Texel.a;

  return FragColour;
}

void main () {
	vec4 texel;
    if( layer < 0.22 )
	{
		texel = texture2D( grass, texture_coords );
	}
	else if( layer < 0.66 )
	{
		texel = texture2D( ground, texture_coords );
	}
	else
	{
		texel = texture2D( snow, texture_coords );
	}
  frag_colour = calculatePointLight( worldVertex, Normal, texel, viewPos, lightPos, lightColor, lightAmbient, lightRadius, specularShiness, specularPower );
}