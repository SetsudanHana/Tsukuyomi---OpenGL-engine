#version 400
layout(location = 20) in vec4 worldVertex;
layout(location = 30) in vec2 texture_coords;
layout(location = 40) in vec4 Normal;


uniform sampler2D sampler;
uniform vec3 viewPos;
uniform vec3 lightDir;
uniform vec3 lightColor;
uniform vec3 lightAmbient;
uniform float specularShiness;
uniform float specularPower;

out vec4 frag_colour;

vec4 calculateDirectionLight(vec4 WorldVertex, vec4 WorldNormal, vec4 Texel, vec3 ViewPos, vec3 LightDir, vec3 LightColor, vec3 LightAmbient, float SpecularShiness, float SpecularPower)
{
  float Id = max(dot(normalize(WorldNormal.xyz), -LightDir), 0.0f);
  vec3 view = normalize(ViewPos - WorldVertex.xyz);
  vec3 H = normalize( -LightDir + view );
  float Is = clamp(dot(normalize(WorldNormal.xyz), H), 0.0, 1.0);
  Is = pow( Is, SpecularShiness ) * ((SpecularShiness + 8.0f) / (8.0f * 3.14159265f)) * Id;

  vec3 SpecularAlbedo = Texel.rgb; //Duzo uproszczenie Kolor DiffuseMesha = Kolor Specular
  vec3 Fresnel = SpecularAlbedo;
  Fresnel += (1.0f - SpecularAlbedo) * pow((1.0f - clamp(dot(H, -LightDir), 0.0f, 1.0f)), 5.0f);

  vec4 FragColour = vec4(LightAmbient, 1.0f) * Texel + Id * vec4(LightColor, 1.0) * Texel  + Is * vec4(Fresnel, 1.0f) * SpecularPower;

  return FragColour;
}

void main () {
  vec4 texel = texture2D(sampler, texture_coords);
  frag_colour = calculateDirectionLight( worldVertex, Normal, texel, viewPos, lightDir, lightColor, lightAmbient, specularShiness, specularPower);
}