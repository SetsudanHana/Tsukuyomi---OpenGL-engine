#version 400
layout(location = 20) in vec4 worldVertex;
layout(location = 30) in vec2 texture_coords;
layout(location = 40) in vec4 Normal;
//layout(location = 50) in vec4 Colour;

uniform sampler2D sampler;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 lightAmbient;
uniform vec3 viewPos;
uniform float lightRadius;
uniform vec3 spotDir;
uniform float cosInner;
uniform float cosOuter;
uniform float specularShiness;
uniform float specularPower;

vec4 calculateSpotLight(vec4 WorldVertex, vec4 WorldNormal, vec4 Texel, vec3 ViewPos, vec3 LightPos, vec3 LightColor, vec3 LightAmbient, float LightRadius, vec3 SpotDir, float CosInner, float CosOuter, float SpecularShiness, float SpecularPower)
{
  vec4 FragColour;
  vec3 lightVec = normalize(-WorldVertex.xyz + LightPos);
  float cos_inner_minus_outer = CosInner - CosOuter;
  float cos_cur_angle = dot(-lightVec.xyz, SpotDir);

  float spot = clamp((cos_cur_angle - CosOuter)/cos_inner_minus_outer, 0.0, 1.0);

  vec3 NormNormal = normalize(WorldNormal.xyz);
  vec3 view = normalize(ViewPos - WorldVertex.xyz);

  vec3 LightDiffuse = dot(NormNormal, lightVec) * LightColor;

  vec3 H = normalize( lightVec + view );
  float Is = clamp(dot(NormNormal, H), 0.0f, 1.0f);
  vec3 Specular = pow( Is, SpecularShiness ) * ((SpecularShiness + 8.0f) / (8.0f * 3.14159265f)) * LightDiffuse;

  vec3 SpecularAlbedo = Texel.rgb; //Duzo uproszczenie Kolor DiffuseMesha = Kolor Specular
  vec3 Fresnel = SpecularAlbedo;
  Fresnel += (1.0f - SpecularAlbedo) * pow((1.0f - clamp(dot(H, lightVec), 0.0f, 1.0f)), 5.0f);

  float lightDist = length(LightPos - WorldVertex.xyz);
  lightDist /= LightRadius;
  float atten = 1.0f/((lightDist * lightDist) + 1);

  FragColour.rgb = LightAmbient * Texel.rgb + spot * atten * LightDiffuse * Texel.rgb + spot * atten * Specular * Fresnel * SpecularPower, 1.0f;
  FragColour.a = Texel.a;

  return FragColour;
}

out vec4 frag_colour;

void main () {
  vec4 texel = texture2D( sampler, texture_coords);
  frag_colour = calculateSpotLight( worldVertex, Normal, texel, viewPos, lightPos, lightColor, lightAmbient, lightRadius, spotDir, cosInner, cosOuter, specularShiness, specularPower);
}
